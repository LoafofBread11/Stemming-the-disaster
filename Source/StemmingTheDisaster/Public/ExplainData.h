// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"

/**
 * 
 */
class STEMMINGTHEDISASTER_API ExplainData
{
public:
	ExplainData();
	~ExplainData();

	UFUNCTION()
	TArray<TPair <FString, FString>> createExplainData(FString mapName);
};
