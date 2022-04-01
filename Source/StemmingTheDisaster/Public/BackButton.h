// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonMain.h"
#include "Kismet/GameplayStatics.h"
#include "SD_GameInstance.h"
#include "BackButton.generated.h"

UCLASS()
class STEMMINGTHEDISASTER_API ABackButton : public AButtonMain
{
	GENERATED_BODY()

public:
	ABackButton();

protected:
	virtual void BeginPlay() override;

public:
	virtual void raiseFlag() override;

	UPROPERTY(VisibleAnywhere)
	USD_GameInstance* GI;
};
