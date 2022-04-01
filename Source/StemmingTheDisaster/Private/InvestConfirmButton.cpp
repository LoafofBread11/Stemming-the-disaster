// Fill out your copyright notice in the Description page of Project Settings.


#include "InvestConfirmButton.h"

AInvestConfirmButton::AInvestConfirmButton()
{
	//constructor
}

void AInvestConfirmButton::BeginPlay()
{
	Super::BeginPlay();
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void AInvestConfirmButton::raiseFlag()
{
	flag = 1;
}

void AInvestConfirmButton::click()
{
	Super::click();
	GI->SetCurrentAction("INVEST");
	raiseFlag();
}

void AInvestConfirmButton::setItem(FString itemName)
{
	item = itemName;
}

void AInvestConfirmButton::setItemDesc(TextComponent newItemDesc)
{
	itemDesc = newItemDesc;
}