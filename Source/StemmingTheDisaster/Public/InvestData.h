// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STEMMINGTHEDISASTER_API InvestData
{
public:
	InvestData();
	~InvestData();

	UFUNCTION()
	TMap<FString, int> createInvestmentData(FString mapName);
};
