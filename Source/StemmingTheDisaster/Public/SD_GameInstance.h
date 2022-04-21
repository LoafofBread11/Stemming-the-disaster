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
		FString currentAction = "IDLE"; 

		UPROPERTY(VisibleAnywhere)
		FString interactableText = "";

		UPROPERTY(VisibleAnywhere)
		FString interactableName = "";

		UPROPERTY(VisibleAnywhere)
		TMap <FString, int> careerPathScores; //scoreList in LucidChart

		UPROPERTY(VisibleAnywhere)
		TMap <FString, int> investmentOptions;

		UPROPERTY(VisibleAnywhere)
		TMap <FString, FString> investmentCareers;

		//UPROPERTY(VisibleAnywhere) Turns out TPair can't be in a UPROPERTY.
		TArray <TPair <FString, FString>> dialogueOptions;

		UPROPERTY(VisibleAnywhere)
		TArray <FString> results;

		UPROPERTY(VisibleAnywhere)
		TArray <FString> travelableMaps; //array of all maps that can be traveled to

		UPROPERTY(VisibleAnywhere)
		TArray<FString> alreadyInvested;

		UPROPERTY(VisibleAnywhere)
			float remainingTime = 1200.0f; //amount of time remaining

		UPROPERTY(VisibleAnywhere)
		int remainingCurrency = 1000000; //amount of currency remaining 

		UFUNCTION(BlueprintCallable)
		void setRemainingTime(float time) { remainingTime = time; }

		UFUNCTION(BlueprintCallable)
		float getRemainingTime() { return remainingTime; }

		UFUNCTION()
		void StartSimulator();

		UFUNCTION()
		void EndSimulator();

		UFUNCTION(BlueprintCallable)
		void SetupMap(FString mapName);

		UFUNCTION()
		TMap<FString, int> GetInvestments();

		UFUNCTION()
		bool MakeInvestment(FString item);

		//UFUNCTION() See above, Can't put UFUNCTION decorations over TPairs
		TArray<TPair <FString, FString>> GetDialouge();

		UFUNCTION()
		void GenerateDialouge(FString dialouge, FString dialogueCode);

		UFUNCTION()
		TArray <FString> GetMaps();

		UFUNCTION()
		void ChangeMap(FString name);

		UFUNCTION(BlueprintCallable)
		FString GetCurrentAction();

		UFUNCTION()
		void SetCurrentAction(FString action);

		UFUNCTION()
		void SetInteractableData(FText name, FText desc);

		UFUNCTION(BlueprintCallable)
		int getCurrencyRemaining();

		UFUNCTION(BlueprintCallable)
		FString getInteractableText();

		UFUNCTION(BlueprintCallable)
		FString getInteractableName();

		UPROPERTY(VisibleAnywhere)
		bool inVR = false;

		UFUNCTION(BlueprintCallable)
		void setInVR(bool mode);

		UFUNCTION(BlueprintCallable)
		bool getInVR();

		//Objects that will hold data for when the map gets populated
		ExplainData exDat;
		InvestData inDat;

		UFUNCTION()
		void scoreInteractable(FString career, int value);

		UFUNCTION()
		FString mapNameLookup(FString name);

};
