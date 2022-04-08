// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplainData.h"

ExplainData::ExplainData()
{
}

ExplainData::~ExplainData()
{
}

TArray<TPair <FString, FString>> ExplainData::createExplainData(FString mapName)
{
	TArray<TPair <FString, FString>> retArr; //Return array that will be populated with data
	if (mapName == "S1VerticalSlice")
	{
		retArr.Add(TPair<FString, FString>("Test Dialogue", "F_test"));
	}

	return retArr; //Return the populated array
}