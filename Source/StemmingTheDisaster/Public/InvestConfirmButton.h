// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonMain.h"
#include "InvestConfirmButton.generated.h"

UCLASS()
class STEMMINGTHEDISASTER_API AInvestConfirmButton : public AButtonMain
{
	GENERATED_BODY()

	public:
		//Sets default values.
		AInvestConfirmButton();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:
		//Variable to hold the name of the item.
		UPROPERTY(VisibleAnywhere)
		FString item;

		//Variable to hold the description of the item.
		UPROPERTY(VisibleAnywhere)
		UTextRenderComponent* itemDesc;

		//Function to raise the flag once the button is pressed.
		virtual void raiseFlag() override;

		virtual void Tick(float DeltaTime) override;

		//Function to set the item's name.
		void setItem(FString itemName);

		//Funtion to set the item's description.
		void setItemDesc(FString newItemDesc);

		//Values for a shake effect for when a bad investment is made
		UPROPERTY(VisibleAnywhere)
		float shakeVal = 0.0f;

		//Starting values for the origin of the button on the x / y plane
		UPROPERTY(VisibleAnywhere)
		float startingY = 0.0f;

		UPROPERTY(VisibleAnywhere)
		float startingX = 0.0f;
};
