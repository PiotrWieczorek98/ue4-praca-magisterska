// Fill out your copyright notice in the Description page of Project Settings.

#include "Comparison.h"


void UComparison::setPositionThreshold(const float value)
{
	this->positionThreshold_ = value;
}

void UComparison::setRotationThreshold(const float value)
{
	this->rotationThreshold_ = value;
}

void UComparison::loadGesturesToCompareTo(const FString fileName)
{
	FString projectDir = FPaths::ProjectDir();
	FString dataDir = "Content/Data/";
	const FString absPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(projectDir, dataDir, fileName));
	TArray<FString> fileContent;

	// Load file
	if (!FFileHelper::LoadFileToStringArrayWithPredicate(fileContent, *absPath,
		[](FString line){return line.Len() > 1;}))
	{
		UE_LOG(LogTemp, Warning, TEXT("UComparison: Gesture To Compare To not loaded!!!"));
		return;
	}
	
	constexpr int bonesInGesture = 24;
	constexpr int gestureDataSize = bonesInGesture * 2;

	if(fileContent.Num() < gestureDataSize)
	{
		UE_LOG(LogTemp, Warning, TEXT("UComparison: File is empty!"));
		return;
	}
	
	int index = 0;
	while(true)
	{
		FGesture gesture;
		gesture.gestureName = fileContent[index];
		index++;
		
		// Loop through bones, *2 because each bone has position and rotation vector
		// Check if loop will reach EOF
		if(index + gestureDataSize >= fileContent.Num())
		{
			return;
		}
		
		for(int i = 0; i<gestureDataSize;i++)
		{
			FVector vec;
			vec.InitFromString(fileContent[index]);
			gesture.bonesData.Add(vec);
			index++;
		}
		this->gestures_.Add(gesture);
	}
}

void UComparison::compareGesture(const TArray<FVector> bonesData, FString& gestureName, float &averageOffset)
{
	constexpr int bonesInGesture = 24;
	constexpr int bonesDataSize = bonesInGesture * 2;
	if (bonesData.Num() < bonesDataSize)
	{
		gestureName = FString("none");
		averageOffset = 0;
		return;
	}
	// Iterate through every gesture
	for (FGesture gesture : this->gestures_)
	{
		bool belowThreshold = true;

		float offsets[bonesDataSize] = {0};
		// Compare each bone position vector
		for(int i = 0; i < bonesInGesture; i++)
		{
			const float vecLen = abs((gesture.bonesData[i] - bonesData[i]).Size());
			if(vecLen > this->positionThreshold_)
			{
				belowThreshold = false;
				break;
			}
			offsets[i] = vecLen;
		}
		// Compare each bone rotation vector
		if(belowThreshold)
		{
			for(int i=24; i < bonesDataSize; i++)
			{
				const float vecLen = abs((gesture.bonesData[i] - bonesData[i]).Size());
				if(vecLen > this->rotationThreshold_)
				{
					belowThreshold = false;
					break;
				}
				offsets[i] = vecLen;
			}			
		}
		
		// If gesture fits below threshold return values
		if(belowThreshold)
		{
			gestureName = gesture.gestureName;
			float offsetSum = 0;
			for (const float offset : offsets)
			{
				offsetSum += offset;
			}
			averageOffset = offsetSum / sizeof(offsets);
			return;
		}
	}
	// If none fit below threshold return none
	gestureName = "none";
	averageOffset = 0;
}
