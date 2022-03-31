// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinationButton.h"

ADestinationButton::ADestinationButton(FString name)
{
	mapName = name;
}

void ADestinationButton::raiseFlag()
{
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UGameplayStatics::OpenLevel((UObject*)GI, FName(mapName));
}
