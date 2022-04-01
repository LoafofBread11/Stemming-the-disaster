// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuButton.h"
AMenuButton::AMenuButton() : AButtonMain()
{

}

void AMenuButton::BeginPlay()
{
	Super::BeginPlay();
}

void AMenuButton::raiseFlag()
{
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

}