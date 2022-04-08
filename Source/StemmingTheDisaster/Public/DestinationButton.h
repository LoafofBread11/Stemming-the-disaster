// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonMain.h"
#include "Kismet/GameplayStatics.h"
#include "SD_GameInstance.h"
#include "DestinationButton.generated.h"

UCLASS()
class STEMMINGTHEDISASTER_API ADestinationButton : public AButtonMain
{
	GENERATED_BODY()

public:
		ADestinationButton();

protected:
		virtual void BeginPlay() override;

public:

		virtual void raiseFlag() override;

		UPROPERTY(VisibleAnywhere)
		USD_GameInstance* GI;

		UPROPERTY(EditAnywhere)
		FString mapName;
};
