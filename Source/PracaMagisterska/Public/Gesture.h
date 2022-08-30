// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gesture.generated.h"


USTRUCT(BlueprintType)
struct FGesture
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gesture")
	FString gestureName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gesture")
	TArray<FVector> bonesData;
};
