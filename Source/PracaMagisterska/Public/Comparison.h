// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define WIN32_LEAN_AND_MEAN

#include "CoreMinimal.h"
#include "Gesture.h"

#include "Comparison.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class PRACAMAGISTERSKA_API UComparison final : public UObject
{
	GENERATED_BODY()
	TArray<FGesture> gestures_;
	float positionThreshold_;
	float rotationThreshold_;

public:
	UFUNCTION(BlueprintCallable, Category = "Comparison")
	void setPositionThreshold(const float value);
	
	UFUNCTION(BlueprintCallable, Category = "Comparison")
	void setRotationThreshold(const float value);
	
	UFUNCTION(BlueprintCallable, Category = "Comparison")
	void loadGesturesToCompareTo(const FString fileName);

	UFUNCTION(BlueprintCallable, Category = "Comparison")
	void compareGesture(const TArray<FVector> bonesData, FString &gestureName, float &averageOffset);

};