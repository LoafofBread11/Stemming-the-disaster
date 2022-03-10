// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SD_GameInstance.generated.h"



/**
 * 
 */
UCLASS()
class STEMMINGTHEDISASTER_API USD_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:

		USD_GameInstance();

		UPROPERTY(VisibleAnywhere)
		FString currentAction; 

		UPROPERTY(VisibleAnywhere)
		FText interactableText;

		UPROPERTY(VisibleAnywhere)
		FText interactableName;

		UPROPERTY(VisibleAnywhere)
		TMap <FString, int> careerPathScores; //scoreList in LucidChart

		UPROPERTY(VisibleAnywhere)
		TMap <FString, int> investmentOptions;

		UPROPERTY(VisibleAnywhere)
		TArray <FString> dialougeOptions;

		UPROPERTY(VisibleAnywhere)
		TArray <FString> results;

		UPROPERTY(VisibleAnywhere)
		TArray <FString> travelableMaps; //array of all maps that can be traveled to

		UPROPERTY(VisibleAnywhere)
		float remainingTime; //amount of time remaining

		UPROPERTY(VisibleAnywhere)
		int remainingCurrency; //amount of currency remaining 

		UFUNCTION(BlueprintCallable)
		void setRemainingTime(float time) { remainingTime = time; }

		UFUNCTION(BlueprintCallable)
		float getRemainingTime() { return remainingTime; }

		UFUNCTION()
		void StartSimulator();

		UFUNCTION()
		void EndSimulator();

		UFUNCTION()
		void SetupMap();

		UFUNCTION()
		int GetInvestment(FString item);

		UFUNCTION()
		void SetInvestment(FString item, int money);

		UFUNCTION()
		bool UpdateInvestment(FString item, int money);

		UFUNCTION()
		TArray<FString> GetDialouge();

		UFUNCTION()
		void GenerateDialouge(FString dialouge);

		UFUNCTION()
		TArray<FString> GetMaps();

		UFUNCTION()
		void ChangeMap(int selection);

		UFUNCTION()
		FString GetCurrentAction();

		UFUNCTION()
		void SetCurrentAction(FString action);

		UFUNCTION()
		void SetInteractableData(FText name, FText desc);

};
