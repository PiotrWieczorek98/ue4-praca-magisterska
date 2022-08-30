// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable: 4883)

#include "CoreMinimal.h"
#include <string>
#include <vector>
#include <fstream>

#include "DecisionTree.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class PRACAMAGISTERSKA_API UDecisionTree final : public UObject
{
	GENERATED_BODY()
private:
	bool classesLoaded_ = false;
	std::vector<std::string> classesNames_;

	static int useClassifier(const float features[72]);
	std::string getClassName(const int index);

public:
	UFUNCTION(BlueprintCallable, Category = "Decision Tree")
	bool loadClasses(const FString fileName);

	UFUNCTION(BlueprintCallable, Category = "Decision Tree")
	void predict(const TArray<float> bonesData, FString& gestureName, int& basedOnSamples);

	UFUNCTION(BlueprintCallable, Category = "Decision Tree")
	void showClassesNames(FString& classesNames);
};