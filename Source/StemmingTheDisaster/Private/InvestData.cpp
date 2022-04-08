// Fill out your copyright notice in the Description page of Project Settings.


#include "InvestData.h"

InvestData::InvestData()
{
}

InvestData::~InvestData()
{
}


TMap<FString, int> InvestData::createInvestmentData(FString mapName)
{
	TMap<FString, int> retMap; //Map that contains what will be returned
	if (mapName == "S1VerticalSlice")
	{
		retMap.Add(TPair<FString, int>("Valid Option", 5));
		retMap.Add(TPair<FString, int>("Invalid Option", 1000001));
	}
	return retMap; //Return the populated map
}


TMap<FString, FString> InvestData::createInvestmentCareerData(FString mapName)
{
	TMap<FString, FString> retMap;

	return retMap;
}