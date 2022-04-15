// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonMain.h"
#include "BackButton.h"
#include "DestinationButton.h"
#include "ExplainButton.h"
#include "InvestConfirmButton.h"
#include "MenuButton.h"
#include "SD_GameInstance.h"
#include "Components/AudioComponent.h"
#include "Narrator.generated.h"

UCLASS()
class STEMMINGTHEDISASTER_API ANarrator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANarrator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void StartTalk();

	UFUNCTION()
	void EndTalk();

	UFUNCTION()
	void CreateInvestMenu();

	UFUNCTION()
	void CreateMainMenu();

	UFUNCTION()
	void CreateTravelMenu();

	UFUNCTION()
	void CreateExplainMenu();

	UFUNCTION()
	void ClearMenu();

	UFUNCTION()
	void HandleFlags();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleAnywhere)
	TArray<AButtonMain*> buttons;

	UPROPERTY(VisibleAnywhere)
	TMap<FString, int> items;

	UPROPERTY(VisibleAnywhere)
	USD_GameInstance* GI;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* explainClip;

	UPROPERTY(VisibleAnywhere)
	float voiceTimeRemaining = 0.0f;

	UFUNCTION()
	void dialogueLookup(int code);
};
