// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinationButton.h"

ADestinationButton::ADestinationButton() : AButtonMain()
{

}

void ADestinationButton::BeginPlay()
{
	Super::BeginPlay();
}

void ADestinationButton::raiseFlag()
{
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(mapName != "")
		UGameplayStatics::OpenLevel((UObject*)GI, FName(mapName));
}
