// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ExplainData.h"
#include "InvestData.h"
#include "Containers/Map.h"
#include "SD_GameInstance.generated.h"

UCLASS()
class STEMMINGTHEDISASTER_API USD_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:

		USD_GameInstance();

		UPROPERTY(VisibleAnywhere)
		FString currentAction = "IDLE"; //Current action, used as a lock and a state variable

		UPROPERTY(VisibleAnywhere)
		FString interactableText = ""; //Text for an interactable, referenced by the UI

		UPROPERTY(VisibleAnywhere)
		FString interactableName = ""; //The name of an interactable currently being displayed, referenced by UI

		UPROPERTY(VisibleAnywhere)
		TMap <FString, int> careerPathScores; //scores of all the investments, known as scoreList in LucidChart

		UPROPERTY(VisibleAnywhere)
		TMap <FString, int> investmentOptions; //Map of all the possible investment options. Key is the name of the investment, Value is the price

		UPROPERTY(VisibleAnywhere)
		TMap <FString, FString> investmentCareers; //Map of every investment to a career. Key is the name of the investment, Value is the career

		//UPROPERTY(VisibleAnywhere) Turns out TPair can't be in a UPROPERTY.
		TArray <TPair <FString, FString>> dialogueOptions; //Array of all the dialogue options. TPair is accessed like a map. Key is the human readable dialogue name, Value is the dialogue code

		UPROPERTY(VisibleAnywhere)
		TArray <FString> results; //Array of the results that is calculated after the simulation concludes.

		UPROPERTY(VisibleAnywhere)
		TArray <FString> travelableMaps; //array of all maps that can be traveled to

		UPROPERTY(VisibleAnywhere)
		TArray<FString> alreadyInvested; //Array of every item that has already been invested in

		UPROPERTY(VisibleAnywhere)
		float remainingTime = 1200.0f; //amount of time remaining

		UPROPERTY(VisibleAnywhere)
		int remainingCurrency = 1000000; //amount of currency remaining 

		UFUNCTION(BlueprintCallable)
		void setRemainingTime(float time) { remainingTime = time; } //Mutator for time

		UFUNCTION(BlueprintCallable)
		float getRemainingTime() { return remainingTime; } //Accessor for time

		UFUNCTION(BlueprintCallable)
		void StartSimulator(FString dis); //Function that resets all of the variables for a new simulation run through. Sets travelable maps based on the input parameter

		UFUNCTION()
		void EndSimulator(); //Calculates and sorts the results of the simulation

		UFUNCTION(BlueprintCallable)
		void SetupMap(FString mapName); //Sets up the investments and dialogue for a given map

		UFUNCTION()
		TMap<FString, int> GetInvestments(); //Returns all possible investments

		UFUNCTION()
		bool MakeInvestment(FString item); //Makes an investment, if possible.

		//UFUNCTION() See above, Can't put UFUNCTION decorations over TPairs
		TArray<TPair <FString, FString>> GetDialouge(); //Returns all possible dialogue options

		UFUNCTION()
		void GenerateDialouge(FString dialouge, FString dialogueCode); //Adds new dialogue to the list of dialogue options

		UFUNCTION()
		TArray <FString> GetMaps(); //Gets all the maps the player can travel to

		UFUNCTION()
		void ChangeMap(FString name); //Creates a fade out cube, and hands it a map parameter to switch to

		UFUNCTION(BlueprintCallable)
		FString GetCurrentAction(); //Retrieves the current action

		UFUNCTION()
		void SetCurrentAction(FString action); //Modifies the current action

		UFUNCTION()
		void SetInteractableData(FText name, FText desc); //Mutates the interactable data

		UFUNCTION(BlueprintCallable)
		int getCurrencyRemaining(); //Accesses the amount of currency remaining

		UFUNCTION(BlueprintCallable)
		FString getInteractableText(); //Accesses the interactable text

		UFUNCTION(BlueprintCallable)
		FString getInteractableName(); //Accesses the interactable name

		UPROPERTY(VisibleAnywhere)
		bool inVR = false; //Variable that stores if the player is in VR. This affects what UI is created and spawn locations

		UFUNCTION(BlueprintCallable)
		void setInVR(bool mode); //Mutator for the inVR variable

		UFUNCTION(BlueprintCallable)
		bool getInVR(); //Accessor for if in VR

		//Objects that will hold data for when the map gets populated
		ExplainData exDat;
		InvestData inDat;

		UFUNCTION()
		void scoreInteractable(FString career, int value); //Scores an interactable or investment in careerpathscores

		UFUNCTION()
		FString mapNameLookup(FString name); //Function that converts the name of a map to a human readable name

		UPROPERTY(EditAnywhere)
		FVector spawnLoc; //Location that the player character was spawned at. Set by the level blueprint

		UPROPERTY(VisibleAnywhere)
		float maxTime = 0.0f; //The maximum amount of time remaining. Referenced by the UI to make the time progress bar always start at 100 %

		UFUNCTION(BlueprintCallable)
		float getMaxTime(); //Accessor for the max time so that it can be accessed by the UI

};
