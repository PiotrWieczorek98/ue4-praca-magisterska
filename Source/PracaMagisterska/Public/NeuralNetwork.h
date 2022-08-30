// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define WIN32_LEAN_AND_MEAN

#include "CoreMinimal.h"
#include <string>
#include <vector>
#include <fdeep/fdeep.hpp>
#include "NeuralNetwork.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PRACAMAGISTERSKA_API UNeuralNetwork : public UObject
{
	GENERATED_BODY()
private:
	bool modelLoaded_ = false;
	bool classesLoaded_ = false;
	std::vector<std::string> classesNames_;
	std::unique_ptr<fdeep::model> model_;

	std::string getClassName(const int index);
public:
	UFUNCTION(BlueprintCallable, Category = "Neural Network")
	bool loadClasses(const FString fileName);

	UFUNCTION(BlueprintCallable, Category = "Neural Network")
	void loadModel(const FString fileName);

	UFUNCTION(BlueprintCallable, Category = "Neural Network")
	void predict(const TArray<float> bonesData, FString& gestureName, float& certainty);
};