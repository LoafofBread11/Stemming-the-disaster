// Fill out your copyright notice in the Description page of Project Settings.


#include "SD_GameInstance.h"

USD_GameInstance::USD_GameInstance()
{
	travelableMaps.Add("Airplane"); //Adding airplane to travelable maps in Sprint 2. Done here only because Start Simulator is not implemented / called yet.
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
	dialogueOptions = exDat.createExplainData(mapName); //Populate the dialogue options
	investmentOptions = inDat.createInvestmentData(mapName); //Populate the investment options
	for (int i = 0; i < alreadyInvested.Num(); i++)
	{
		if (investmentOptions.Contains(alreadyInvested[i])) //Check if it's been invested in
		{
			investmentOptions.Remove(alreadyInvested[i]); //Remove it if we find it
			UE_LOG(LogTemp, Warning, TEXT("Removed an Element!"));
		}
	}
	investmentCareers = inDat.createInvestmentCareerData(mapName); //Populate the careers associated with the investment options

	if (mapName == "Results")
		currentAction = "RESULTS";
	else if (mapName == "StartMap" || mapName == "Airplane") //If we're in the start map or the airplane
		currentAction = "START";
	else
		currentAction = "IDLE";
	return;
}

TMap<FString, int> USD_GameInstance::GetInvestments()
{
	return investmentOptions;
}


bool USD_GameInstance::MakeInvestment(FString item)
{
	int *invest = investmentOptions.Find(item);
	if (invest != nullptr) //basically, if the item was an investment option...
	{	
		int cost = *invest; //storing the cost of the item
		if (cost <= remainingCurrency) //See if there is enough funds
		{
			remainingCurrency = remainingCurrency - cost; //Subtract the currency
			FString* career = investmentCareers.Find(item); //Find the relevant career
			if (career != nullptr) //If the career was found
			{
				scoreInteractable(*career, cost); //Score the career
			}
			investmentOptions.Remove(item); //Remove the item from the investments
			alreadyInvested.Add(item); //Add the item to the list of already invested things
			return true;
		}
		else {
			return false; //Not enough funds
		}
	}
	return false; //Item didn't exist
}

TArray<TPair <FString, FString>> USD_GameInstance::GetDialouge()
{
	return dialogueOptions;
}

void USD_GameInstance::GenerateDialouge(FString dialogue, FString dialogueCode)
{
	dialogueOptions.Add(TPair<FString, FString>(dialogue, dialogueCode));
	return;
}

TArray <FString> USD_GameInstance::GetMaps()
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

FString USD_GameInstance::mapNameLookup(FString name)
{
	if (name == "Airplane")
		return TEXT("Air Plane");
	return TEXT(""); //If we get nothing, return nothing
}