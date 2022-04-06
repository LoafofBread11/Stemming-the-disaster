// Fill out your copyright notice in the Description page of Project Settings.


#include "InvestConfirmButton.h"

AInvestConfirmButton::AInvestConfirmButton() : AButtonMain()
{
	itemDesc = CreateDefaultSubobject<UTextRenderComponent>("Investment Name");
	itemDesc->SetupAttachment(RootComponent); //Setup attachment to the rest of the button
	itemDesc->SetRelativeLocationAndRotation(FVector(100.0f, 0.0f, 0.0f), FRotator(0.0f, 90.0f, 0.0f)); //Position text accordingly
	itemDesc->SetHorizontalAlignment(EHTA_Left);
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