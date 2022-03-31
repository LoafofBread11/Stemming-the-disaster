// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonMain.h"
#include "Kismet/GameplayStatics.h"
#include "SD_GameInstance.h"


class STEMMINGTHEDISASTER_API ADestinationButton : public AButtonMain
{
	public:
		UPROPERTY(VisibleAnywhere)
		FString mapName;
		UFUNCTION()
		ADestinationButton(FString name);
		UFUNCTION()
		void raiseFlag();

		UPROPERTY(VisibleAnywhere)
		USD_GameInstance* GI;
};
