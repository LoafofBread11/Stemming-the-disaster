// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SD_GameInstance.h"
#include "ButtonMain.h"
#include "ExplainButton.generated.h"

UCLASS()
class STEMMINGTHEDISASTER_API AExplainButton : public AButtonMain
{
	GENERATED_BODY()

public:
	AExplainButton();

protected:
		
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere)
	FString dialogueCode;

	UPROPERTY(VisibleAnywhere)
	USD_GameInstance* GI;

	virtual void raiseFlag() override;

	void click() override;
};
