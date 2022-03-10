// Fill out your copyright notice in the Description page of Project Settings.


#include "SD_GameInstance.h"

USD_GameInstance::USD_GameInstance()
{

}

void USD_GameInstance::StartSimulator()
{
	return;
}

void USD_GameInstance::EndSimulator()
{
	return;
}

void USD_GameInstance::SetupMap()
{
	return;
}

int USD_GameInstance::GetInvestment(FString item)
{
	return 0;
}

void USD_GameInstance::SetInvestment(FString item, int money)
{
	return;
}

bool USD_GameInstance::UpdateInvestment(FString item, int money)
{
	return true;
}

TArray<FString> USD_GameInstance::GetDialouge()
{
	return dialougeOptions;
}

void USD_GameInstance::GenerateDialouge(FString dialogue)
{
	return;
}

TArray<FString> USD_GameInstance::GetMaps()
{
	return travelableMaps;
}

void USD_GameInstance::ChangeMap(int selection)
{
	return;
}

FString USD_GameInstance::GetCurrentAction()
{
	return currentAction;
}

void USD_GameInstance::SetCurrentAction(FString action)
{
	currentAction = action;
}

void USD_GameInstance::SetInteractableData(FText name, FText desc)
{
	return;
}

