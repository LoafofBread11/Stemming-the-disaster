// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonMain.h"
#include "InvestConfirmButton.generated.h"

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
		TextComponent itemDesc;

		//Flag for the button
		UPROPERTY(VisibleAnywhere)
		int flag = -1;

		//Copy of the game instance.
		UPROPERTY(VisibleAnywhere)
		USD_GameInstance* GI;

		//Function to raise the flag once the button is pressed.
		virtual void raiseFlag() override;

		//Function for when the button is clicked.
		void click() override;

		//Function to set the item's name.
		void setItem(FString itemName);

		//Funtion to set the item's description.
		void setItemDesc(TextComponent newItemDesc);
};
