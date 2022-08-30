// Fill out your copyright notice in the Description page of Project Settings.

#include "DecisionTree.h"

std::string UDecisionTree::getClassName(const int index)
{
    if (!this->classesLoaded_)
    {
        return std::string("UDecisionTree: Classes not loaded!");
    }

    if (this->classesNames_.size() - 1 < index)
    {
        return std::string("UDecisionTree: No class for such index: " + std::to_string(index));
    }
    else
    {
        return this->classesNames_[index];
    }
}


bool UDecisionTree::loadClasses(const FString fileName)
{
    FString projectDir = FPaths::ProjectDir();
    FString dataDir = "Content/Data/";
    const FString absPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(projectDir, dataDir, fileName));
    TArray<FString> fileContent;
    if (!FFileHelper::LoadFileToStringArray(fileContent, *absPath))
    {
        UE_LOG(LogTemp, Warning, TEXT("UDecisionTree: Classes File not loaded!!!"));
        this->classesLoaded_ = false;
        return false;
    }

    for (FString line : fileContent)
    {
        std::string lineStr = TCHAR_TO_UTF8(*line);
        this->classesNames_.push_back(lineStr);;
    }
    
    this->classesLoaded_ = true;
    return true;
}

void UDecisionTree::predict(const TArray<float> bonesData, FString& gestureName, int& basedOnSamples)
{
    // bonesDataSize = bonesInGesture * 2 because each bone has 2 vectors - position and rotation 
    constexpr int bonesInGesture = 24, vectorSize = 3;
    constexpr int bonesDataSize = bonesInGesture * 2 * vectorSize;

    if (bonesData.Num() < bonesDataSize)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDecisionTree: Input size incorect!!!"));
        gestureName = FString("none");
        basedOnSamples = -1;
        return;
    }

    // Convert TArray to array
    float sample [bonesDataSize] = {0};
    for (int i = 0; i < bonesData.Num(); i++)
    {
        sample[i] = bonesData[i];
    }

    // Get decision tree classification
    const int classIndex = this->useClassifier(sample);
    const std::string className = this->getClassName(classIndex);

    // convert result to FString
    gestureName = FString(className.c_str());
    basedOnSamples = 1;
    return;
}

void UDecisionTree::showClassesNames(FString& classesNames)
{
    for (int i = 0; i < this->classesNames_.size(); i++)
    {
        classesNames += FString(classesNames_[i].c_str());
    }
}


int UDecisionTree::useClassifier(const float features[144])
{
    int classes[16];
        
    if (features[135] <= 84.56600189208984) {
        if (features[62] <= -8.21399974822998) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 0; 
            classes[6] = 0; 
            classes[7] = 0; 
            classes[8] = 0; 
            classes[9] = 0; 
            classes[10] = 0; 
            classes[11] = 0; 
            classes[12] = 81; 
            classes[13] = 0; 
            classes[14] = 0; 
            classes[15] = 0; 
        } else {
            if (features[16] <= -9.626500129699707) {
                if (features[42] <= 0.9995000064373016) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                    classes[6] = 0; 
                    classes[7] = 86; 
                    classes[8] = 0; 
                    classes[9] = 0; 
                    classes[10] = 0; 
                    classes[11] = 0; 
                    classes[12] = 0; 
                    classes[13] = 0; 
                    classes[14] = 0; 
                    classes[15] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                    classes[6] = 0; 
                    classes[7] = 0; 
                    classes[8] = 0; 
                    classes[9] = 0; 
                    classes[10] = 0; 
                    classes[11] = 0; 
                    classes[12] = 0; 
                    classes[13] = 0; 
                    classes[14] = 4; 
                    classes[15] = 0; 
                }
            } else {
                if (features[13] <= -6.6584999561309814) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                    classes[6] = 80; 
                    classes[7] = 0; 
                    classes[8] = 0; 
                    classes[9] = 0; 
                    classes[10] = 0; 
                    classes[11] = 0; 
                    classes[12] = 0; 
                    classes[13] = 0; 
                    classes[14] = 0; 
                    classes[15] = 0; 
                } else {
                    if (features[82] <= 51.45199966430664) {
                        if (features[133] <= -5.864000082015991) {
                            if (features[128] <= 14.436498641967773) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                                classes[6] = 0; 
                                classes[7] = 0; 
                                classes[8] = 0; 
                                classes[9] = 83; 
                                classes[10] = 0; 
                                classes[11] = 0; 
                                classes[12] = 0; 
                                classes[13] = 0; 
                                classes[14] = 0; 
                                classes[15] = 0; 
                            } else {
                                if (features[84] <= -4.096000671386719) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                    classes[6] = 0; 
                                    classes[7] = 0; 
                                    classes[8] = 0; 
                                    classes[9] = 0; 
                                    classes[10] = 75; 
                                    classes[11] = 0; 
                                    classes[12] = 0; 
                                    classes[13] = 0; 
                                    classes[14] = 0; 
                                    classes[15] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 78; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                    classes[6] = 0; 
                                    classes[7] = 0; 
                                    classes[8] = 0; 
                                    classes[9] = 0; 
                                    classes[10] = 0; 
                                    classes[11] = 0; 
                                    classes[12] = 0; 
                                    classes[13] = 0; 
                                    classes[14] = 0; 
                                    classes[15] = 0; 
                                }
                            }
                        } else {
                            if (features[86] <= 111.93899917602539) {
                                if (features[54] <= 2.05649995803833) {
                                    if (features[62] <= -2.519999921321869) {
                                        classes[0] = 0; 
                                        classes[1] = 0; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                        classes[4] = 79; 
                                        classes[5] = 0; 
                                        classes[6] = 0; 
                                        classes[7] = 0; 
                                        classes[8] = 0; 
                                        classes[9] = 0; 
                                        classes[10] = 0; 
                                        classes[11] = 0; 
                                        classes[12] = 0; 
                                        classes[13] = 0; 
                                        classes[14] = 0; 
                                        classes[15] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 0; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                        classes[4] = 0; 
                                        classes[5] = 1; 
                                        classes[6] = 0; 
                                        classes[7] = 0; 
                                        classes[8] = 0; 
                                        classes[9] = 0; 
                                        classes[10] = 0; 
                                        classes[11] = 0; 
                                        classes[12] = 0; 
                                        classes[13] = 0; 
                                        classes[14] = 0; 
                                        classes[15] = 0; 
                                    }
                                } else {
                                    if (features[85] <= 37.970001220703125) {
                                        if (features[143] <= -72.07400131225586) {
                                            if (features[90] <= 95.09650039672852) {
                                                classes[0] = 0; 
                                                classes[1] = 0; 
                                                classes[2] = 0; 
                                                classes[3] = 76; 
                                                classes[4] = 0; 
                                                classes[5] = 0; 
                                                classes[6] = 0; 
                                                classes[7] = 0; 
                                                classes[8] = 0; 
                                                classes[9] = 0; 
                                                classes[10] = 0; 
                                                classes[11] = 0; 
                                                classes[12] = 0; 
                                                classes[13] = 0; 
                                                classes[14] = 0; 
                                                classes[15] = 0; 
                                            } else {
                                                classes[0] = 0; 
                                                classes[1] = 0; 
                                                classes[2] = 0; 
                                                classes[3] = 0; 
                                                classes[4] = 0; 
                                                classes[5] = 0; 
                                                classes[6] = 0; 
                                                classes[7] = 0; 
                                                classes[8] = 0; 
                                                classes[9] = 0; 
                                                classes[10] = 0; 
                                                classes[11] = 0; 
                                                classes[12] = 0; 
                                                classes[13] = 0; 
                                                classes[14] = 1; 
                                                classes[15] = 0; 
                                            }
                                        } else {
                                            if (features[115] <= -26.17549991607666) {
                                                if (features[126] <= -7.608501434326172) {
                                                    if (features[101] <= 94.49850082397461) {
                                                        classes[0] = 0; 
                                                        classes[1] = 0; 
                                                        classes[2] = 0; 
                                                        classes[3] = 0; 
                                                        classes[4] = 1; 
                                                        classes[5] = 0; 
                                                        classes[6] = 0; 
                                                        classes[7] = 0; 
                                                        classes[8] = 0; 
                                                        classes[9] = 0; 
                                                        classes[10] = 0; 
                                                        classes[11] = 0; 
                                                        classes[12] = 0; 
                                                        classes[13] = 0; 
                                                        classes[14] = 0; 
                                                        classes[15] = 0; 
                                                    } else {
                                                        classes[0] = 0; 
                                                        classes[1] = 0; 
                                                        classes[2] = 0; 
                                                        classes[3] = 0; 
                                                        classes[4] = 0; 
                                                        classes[5] = 0; 
                                                        classes[6] = 0; 
                                                        classes[7] = 0; 
                                                        classes[8] = 0; 
                                                        classes[9] = 0; 
                                                        classes[10] = 0; 
                                                        classes[11] = 0; 
                                                        classes[12] = 0; 
                                                        classes[13] = 0; 
                                                        classes[14] = 2; 
                                                        classes[15] = 0; 
                                                    }
                                                } else {
                                                    classes[0] = 82; 
                                                    classes[1] = 0; 
                                                    classes[2] = 0; 
                                                    classes[3] = 0; 
                                                    classes[4] = 0; 
                                                    classes[5] = 0; 
                                                    classes[6] = 0; 
                                                    classes[7] = 0; 
                                                    classes[8] = 0; 
                                                    classes[9] = 0; 
                                                    classes[10] = 0; 
                                                    classes[11] = 0; 
                                                    classes[12] = 0; 
                                                    classes[13] = 0; 
                                                    classes[14] = 0; 
                                                    classes[15] = 0; 
                                                }
                                            } else {
                                                if (features[21] <= -1.934999942779541) {
                                                    if (features[58] <= -8.64650011062622) {
                                                        classes[0] = 0; 
                                                        classes[1] = 0; 
                                                        classes[2] = 0; 
                                                        classes[3] = 0; 
                                                        classes[4] = 0; 
                                                        classes[5] = 0; 
                                                        classes[6] = 0; 
                                                        classes[7] = 0; 
                                                        classes[8] = 0; 
                                                        classes[9] = 0; 
                                                        classes[10] = 0; 
                                                        classes[11] = 0; 
                                                        classes[12] = 0; 
                                                        classes[13] = 0; 
                                                        classes[14] = 73; 
                                                        classes[15] = 0; 
                                                    } else {
                                                        classes[0] = 0; 
                                                        classes[1] = 0; 
                                                        classes[2] = 0; 
                                                        classes[3] = 0; 
                                                        classes[4] = 0; 
                                                        classes[5] = 0; 
                                                        classes[6] = 0; 
                                                        classes[7] = 0; 
                                                        classes[8] = 0; 
                                                        classes[9] = 1; 
                                                        classes[10] = 0; 
                                                        classes[11] = 0; 
                                                        classes[12] = 0; 
                                                        classes[13] = 0; 
                                                        classes[14] = 0; 
                                                        classes[15] = 0; 
                                                    }
                                                } else {
                                                    classes[0] = 0; 
                                                    classes[1] = 0; 
                                                    classes[2] = 0; 
                                                    classes[3] = 0; 
                                                    classes[4] = 0; 
                                                    classes[5] = 0; 
                                                    classes[6] = 0; 
                                                    classes[7] = 0; 
                                                    classes[8] = 72; 
                                                    classes[9] = 0; 
                                                    classes[10] = 0; 
                                                    classes[11] = 0; 
                                                    classes[12] = 0; 
                                                    classes[13] = 0; 
                                                    classes[14] = 0; 
                                                    classes[15] = 0; 
                                                }
                                            }
                                        }
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 0; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                        classes[4] = 0; 
                                        classes[5] = 0; 
                                        classes[6] = 0; 
                                        classes[7] = 0; 
                                        classes[8] = 0; 
                                        classes[9] = 0; 
                                        classes[10] = 0; 
                                        classes[11] = 0; 
                                        classes[12] = 0; 
                                        classes[13] = 76; 
                                        classes[14] = 0; 
                                        classes[15] = 0; 
                                    }
                                }
                            } else {
                                if (features[127] <= 19.327000617980957) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 79; 
                                    classes[6] = 0; 
                                    classes[7] = 0; 
                                    classes[8] = 0; 
                                    classes[9] = 0; 
                                    classes[10] = 0; 
                                    classes[11] = 0; 
                                    classes[12] = 0; 
                                    classes[13] = 0; 
                                    classes[14] = 0; 
                                    classes[15] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                    classes[6] = 0; 
                                    classes[7] = 0; 
                                    classes[8] = 0; 
                                    classes[9] = 0; 
                                    classes[10] = 0; 
                                    classes[11] = 0; 
                                    classes[12] = 0; 
                                    classes[13] = 0; 
                                    classes[14] = 0; 
                                    classes[15] = 79; 
                                }
                            }
                        }
                    } else {
                        if (features[91] <= 37.49349927902222) {
                            classes[0] = 0; 
                            classes[1] = 83; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                            classes[6] = 0; 
                            classes[7] = 0; 
                            classes[8] = 0; 
                            classes[9] = 0; 
                            classes[10] = 0; 
                            classes[11] = 0; 
                            classes[12] = 0; 
                            classes[13] = 0; 
                            classes[14] = 0; 
                            classes[15] = 0; 
                        } else {
                            if (features[104] <= 5.576999664306641) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                                classes[6] = 0; 
                                classes[7] = 0; 
                                classes[8] = 0; 
                                classes[9] = 0; 
                                classes[10] = 2; 
                                classes[11] = 0; 
                                classes[12] = 0; 
                                classes[13] = 0; 
                                classes[14] = 0; 
                                classes[15] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                                classes[6] = 0; 
                                classes[7] = 0; 
                                classes[8] = 0; 
                                classes[9] = 0; 
                                classes[10] = 0; 
                                classes[11] = 0; 
                                classes[12] = 0; 
                                classes[13] = 1; 
                                classes[14] = 0; 
                                classes[15] = 0; 
                            }
                        }
                    }
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
        classes[6] = 0; 
        classes[7] = 0; 
        classes[8] = 0; 
        classes[9] = 0; 
        classes[10] = 0; 
        classes[11] = 85; 
        classes[12] = 0; 
        classes[13] = 0; 
        classes[14] = 0; 
        classes[15] = 0; 
    }

    int index = 0;
    for (int i = 0; i < 16; i++) {
        index = classes[i] > classes[index] ? i : index;
    }
    return index;
}