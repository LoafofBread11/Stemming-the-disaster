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

void USD_GameInstance::SetupMap(FString mapName)
{
	//Setup variables upon the switching of maps. Called by level blueprint
	dialogueOptions = exDat.createExplainData(mapName);
	investmentOptions = inDat.createInvestmentData(mapName);
	return;
}

TMap<FString, int> USD_GameInstance::GetInvestments()
{
	return investmentOptions;
}


bool USD_GameInstance::MakeInvestment(FString item)
{
	return true;
}

TArray<TPair <FString, FString>> USD_GameInstance::GetDialouge()
{
	return dialogueOptions;
}

void USD_GameInstance::GenerateDialouge(FString dialogue, FString dialogueCode)
{
	//dialogueOptions.Add(TPair<FString, FString>("", ""));
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
	interactableName = name.ToString();
	interactableText = desc.ToString();
	return;
}

int USD_GameInstance::getCurrencyRemaining()
{
	return remainingCurrency;
}

FString USD_GameInstance::getInteractableText()
{
	return interactableText;
}

FString USD_GameInstance::getInteractableName()
{
	return interactableName;
}

void USD_GameInstance::setInVR(bool mode)
{
	inVR = mode;
}

bool USD_GameInstance::getInVR()
{
	return inVR;
}

void USD_GameInstance::scoreInteractable(FString career, int value)
{
	int* result = careerPathScores.Find(career);
	if (result != nullptr) //If the map contains the career already
	{
		int scoreSum = *result + value;
		careerPathScores.Remove(career);
		careerPathScores.Add(career, scoreSum);
		UE_LOG(LogTemp, Warning, TEXT("Value changed: map value has a value of %d"), scoreSum);
	}
	else
	{
		careerPathScores.Add(career, value);
	}
}