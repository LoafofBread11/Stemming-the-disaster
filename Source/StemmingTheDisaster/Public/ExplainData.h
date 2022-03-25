// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STEMMINGTHEDISASTER_API ExplainData
{
public:
	ExplainData();
	~ExplainData();

	UFUNCTION()
	TArray<FString> createExplainData(FString mapName);
};
