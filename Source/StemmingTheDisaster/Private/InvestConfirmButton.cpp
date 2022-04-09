// Fill out your copyright notice in the Description page of Project Settings.


#include "InvestConfirmButton.h"

AInvestConfirmButton::AInvestConfirmButton() : AButtonMain()
{
	itemDesc = CreateDefaultSubobject<UTextRenderComponent>("Investment Name");
	itemDesc->SetupAttachment(RootComponent); //Setup attachment to the rest of the button
	itemDesc->SetRelativeLocationAndRotation(FVector(-100.0f, 0.0f, 0.0f), FRotator(0.0f, 90.0f, 0.0f)); //Position text accordingly
	itemDesc->SetHorizontalAlignment(EHTA_Right);
}

void AInvestConfirmButton::BeginPlay()
{
	Super::BeginPlay();
	itemDesc->SetRelativeScale3D(Text->GetRelativeScale3D()); //Make the 2 texts fields have parity with each other
}

void AInvestConfirmButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isPressed >= 0.0f)
	{
		itemDesc->SetWorldScale3D(FVector(normalScaleText, normalScaleText, normalScaleText));
	}
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