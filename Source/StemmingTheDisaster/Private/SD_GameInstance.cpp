// Fill out your copyright notice in the Description page of Project Settings.

#include "FadeOutTravelCube.h"
#include "SD_GameInstance.h"

USD_GameInstance::USD_GameInstance()
{
	travelableMaps.Add("Airplane"); //Adding airplane to travelable maps in Sprint 2. Done here only because Start Simulator is not implemented / called yet.
}

void USD_GameInstance::StartSimulator(FString dis)
{
	//Clear / Reset all of the default values
	remainingTime = 15.0f; //Reset Time
	dialogueOptions.Empty(); //Empty the Dialogue Options
	investmentOptions.Empty(); //Empty the investment options
	investmentCareers.Empty(); //Empty the investment's associated careers
	travelableMaps.Empty(); //Empty the travelable maps
	careerPathScores.Empty(); //Empty the scores
	results.Empty(); //Empty the results
	if (dis == "Harvey")
	{
		//Add the maps that we can travel to here
	}
	return;
}

void USD_GameInstance::EndSimulator()
{
	careerPathScores.ValueSort([](int A, int B) {
		return A > B; //Sort the values in career path in descending order
		});
	for (auto It = careerPathScores.CreateConstIterator(); It; ++It) //For the entire map
	{
		results.Add(It->Key); //Add the sorted career scores to the results array. It will be referenced in the results map
		UE_LOG(LogTemp, Warning, TEXT("%s Added to results"), *It->Key);
	}
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

	//Set current action based on what map is loaded in
	if (mapName == "Results")
		currentAction = "RESULTS";
	else if (mapName == "StartMap" || mapName == "Airplane") //If we're in the start map or the airplane
		currentAction = "START";
	else
		currentAction = "IDLE";

	//Set the spawn location, used for transitions
	if (mapName == "Results" || mapName == "StartMap" || mapName == "S1VerticalSlice")
		spawnLoc = FVector(0.0f, 0.0f, 6.25f);
	else if (mapName == "Airplane")
		spawnLoc = FVector(-210.0f, -200.0f, 15.0f);
	return;
}

TMap<FString, int> USD_GameInstance::GetInvestments()
{
	return investmentOptions;
}


bool USD_GameInstance::MakeInvestment(FString item)
{
	int *invest = investmentOptions.Find(item); //Try to find the associated investment
	if (invest != nullptr) //If the investment exists
	{	
		int cost = *invest; //store the cost of the item
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
	return dialogueOptions; //Return the dialogue options so that they can be displayed in menus
}

void USD_GameInstance::GenerateDialouge(FString dialogue, FString dialogueCode)
{
	dialogueOptions.Add(TPair<FString, FString>(dialogue, dialogueCode)); //Add a new dialogue option to the list of dialogue option
	return;
}

TArray <FString> USD_GameInstance::GetMaps()
{
	return travelableMaps; //Return a list of maps that can be traveled to.
}

void USD_GameInstance::ChangeMap(FString name)
{
	if (!inVR) //If not in VR
		spawnLoc.Z += 125; //Increase the height of the box to be at the camera height

	AFadeOutTravelCube* newCube = GetWorld()->SpawnActor<AFadeOutTravelCube>(AFadeOutTravelCube::StaticClass(), spawnLoc, FRotator(0.0f)); //Spawn the travel cube
	newCube->mapName = name;
	SetCurrentAction("TRAVELING"); //Ensure no actions can occur while we are traveling
	if (!inVR) //If not in VR
		spawnLoc.Z -= 125; //Reset the camera height
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
		UE_LOG(LogTemp, Warning, TEXT("Value changed: career %s has a value of %d"), *career, scoreSum);
	}
	else
	{
		careerPathScores.Add(career, value);
	}
}

FString USD_GameInstance::mapNameLookup(FString name)
{
	//Compare the sent in name to different names to see if a match is given. Some maps may already be human readable.
	if (name == "Airplane")
		return TEXT("Air Plane");
	return name; //If nothing was found, simply return what was sent.
}