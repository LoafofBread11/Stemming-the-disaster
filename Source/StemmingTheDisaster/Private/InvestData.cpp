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
	else if (mapName == "CivilEngineering")
	{
		retMap.Add(TPair<FString, int>("Repair Sinkhole and Overpass", 100000));
		retMap.Add(TPair<FString, int>("Research New Ways to Make Roads Stronger", 125000));
	}
	else if (mapName == "KingwoodFlood")
	{
		retMap.Add(TPair<FString, int>("Floodplane Research", 100000));
		retMap.Add(TPair<FString, int>("Develop Emergency Measures for Flooding", 125000));
	}
	else if (mapName == "Shelter")
	{

	}
	else if (mapName == "RescueStation")
	{

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
	else if (mapName == "CivilEngineering")
	{
		retMap.Add(TPair<FString, FString>("Repair Sinkhole and Overpass", "Construction Civil Engineering"));
		retMap.Add(TPair<FString, FString>("Research New Ways to Make Roads Stronger", "Traffic Engineer"));
	}
	else if (mapName == "KingwoodFlood")
	{
		retMap.Add(TPair<FString, FString>("Floodplane Research", "Urban Planning"));
		retMap.Add(TPair<FString, FString>("Develop Emergency Measures for Flooding", "Emergency Management Engineer"));
	}
	else if (mapName == "Shelter")
	{

	}
	else if (mapName == "RescueStation")
	{

	}

	return retMap;
}