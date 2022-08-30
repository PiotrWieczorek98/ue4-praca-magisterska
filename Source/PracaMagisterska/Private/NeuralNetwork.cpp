// Fill out your copyright notice in the Description page of Project Settings.
#include "NeuralNetwork.h"


bool UNeuralNetwork::loadClasses(const FString fileName)
{
    FString projectDir = FPaths::ProjectDir();
    FString dataDir = "Content/Data/";
    const FString absPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(projectDir, dataDir, fileName));
    TArray<FString> fileContent;
    if (!FFileHelper::LoadFileToStringArray(fileContent, *absPath))
    {
        UE_LOG(LogTemp, Warning, TEXT("Classes File not loaded!!!"));
        this->classesLoaded_ = false;
        return false;
    }
    for (FString line : fileContent)
    {
        std::string lineStr = TCHAR_TO_UTF8(*line);
        this->classesNames_.push_back(lineStr);
    }
    UE_LOG(LogTemp, Warning, TEXT("UNeuralNetwork: Loaded %d classes"), static_cast<int>(this->classesNames_.size()));
    this->classesLoaded_ = true;
    return true;
}

std::string UNeuralNetwork::getClassName(const int index)
{
    if (!this->classesLoaded_)
    {
        return std::string("UNeuralNetwork: Classes not loaded!");
    }

    if (this->classesNames_.size() - 1 < index)
    {
        return std::string("UNeuralNetwork: No class for such index: " + std::to_string(index));
    }

    return this->classesNames_[index];
}

void UNeuralNetwork::loadModel(const FString fileName)
{
    FString projectDir = FPaths::ProjectDir();
    FString dataDir = "Content/Data/";
    const FString absPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(projectDir, dataDir, fileName));
    FString fileContent;
    if (!FFileHelper::LoadFileToString(fileContent, *absPath))
    {
        UE_LOG(LogTemp, Warning, TEXT("UNeuralNetwork:  model file not loaded!!!"));
        return;
    }
    const std::string fileContentString = TCHAR_TO_UTF8(*fileContent);

    
    this->model_ = std::make_unique<fdeep::model>(fdeep::read_model_from_string(fileContentString));
    this->modelLoaded_ = true;
}

void UNeuralNetwork::predict(const TArray<float> bonesData, FString& gestureName, float& certainty)
{
    // bonesDataSize = bonesInGesture * 2 because each bone has 2 vectors - position and rotation 
    constexpr int bonesInGesture = 24, vectorSize = 3;
    constexpr int bonesDataSize = bonesInGesture * 2 * vectorSize;
    if (!this->modelLoaded_)
    {
        UE_LOG(LogTemp, Warning, TEXT("UNeuralNetwork: Model NOT loaded!!!"));
        gestureName = FString("UNeuralNetwork: Model NOT loaded!!!");
        certainty = -1;
        return;
    }

    if (bonesData.Num() < bonesDataSize)
    {
        UE_LOG(LogTemp, Warning, TEXT("UNeuralNetwork: Input size incorect!!!"));
        gestureName = FString("UNeuralNetwork: Input size incorrect!!!");
        certainty = -1;
        return;
    }

    // Convert TArray to vector
    std::vector<float> inputVec;
    for (int i = 0; i < bonesData.Num(); i++)
    {
        inputVec.push_back(bonesData[i]);
    }

    // Create tensor
    const fdeep::tensor_shape shape = fdeep::tensor_shape(bonesDataSize);
    const fdeep::tensor inputTensor = fdeep::tensor(shape, inputVec);

    // Get prediction
    const fdeep::tensors prediction = this->model_->predict({ inputTensor });
    const fdeep::internal::shared_float_vec predictionVector = prediction.front().as_vector();

    // convert results to std::vector 
    std::vector<float> predictionStdVector;
    for (int i = 0; i < predictionVector->size(); i++)
    {
        predictionStdVector.push_back(predictionVector->at(i));
    }
    // Find index of max value
    float maxVal = 0;
    int maxValIndex = 0;
    for (int i = 0; i < predictionStdVector.size(); i++)
    {
        if (predictionStdVector[i] > maxVal)
        {
            maxVal = predictionStdVector[i];
            maxValIndex = i;
        }
    }

    const std::string className = this->getClassName(maxValIndex);
    gestureName = FString(className.c_str());
    certainty = maxVal * 100;
}