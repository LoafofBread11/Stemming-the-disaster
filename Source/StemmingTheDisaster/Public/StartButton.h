// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestinationButton.h"
#include "StartButton.generated.h"

/**
 * 
 */
UCLASS()
class STEMMINGTHEDISASTER_API AStartButton : public ADestinationButton
{
	GENERATED_BODY()

	public:
		AStartButton(); //Constructor

	protected:
		virtual void BeginPlay() override;

	public:

		virtual void raiseFlag() override;

		UPROPERTY(EditAnywhere)
		FString simulationName; //Name of the simulation
};
