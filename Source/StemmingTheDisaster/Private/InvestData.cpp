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
	else if (mapName == "InternetOutage")
	{
		retMap.Add(TPair<FString, int>("Repair Cell Tower", 100000));
		retMap.Add(TPair<FString, int>("Clear Downed Cables and Repair Electricity", 125000));
	}
	return retMap; //Return the populated map
}


TMap<FString, FString> InvestData::createInvestmentCareerData(FString mapName)
{
	TMap<FString, FString> retMap;
	if (mapName == "S1VerticalSlice")
	{
		retMap.Add(TPair<FString, FString>("Valid Option", "TestCareer"));
	}

	else if (mapName == "InternetOutage")
	{
		retMap.Add(TPair<FString, FString>("Repair Cell Tower", "Network Engineer"));
		retMap.Add(TPair<FString, FString>("Clear Downed Cables and Repair Electricity", "Electrical Engineer"));
		
	}

	return retMap;
}