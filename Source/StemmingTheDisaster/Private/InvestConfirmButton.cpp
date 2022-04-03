// Fill out your copyright notice in the Description page of Project Settings.


#include "InvestConfirmButton.h"

AInvestConfirmButton::AInvestConfirmButton() : AButtonMain()
{
	itemDesc = CreateDefaultSubobject<UTextRenderComponent>("Investment Name");
}

void AInvestConfirmButton::BeginPlay()
{
	Super::BeginPlay();
}

void AInvestConfirmButton::raiseFlag()
{
	flag = 1;
}

void AInvestConfirmButton::setItem(FString itemName)
{
	item = itemName;
}

void AInvestConfirmButton::setItemDesc(FString newItemDesc)
{
	itemDesc->SetText(newItemDesc);
}