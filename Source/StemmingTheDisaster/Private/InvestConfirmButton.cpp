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
	ButtonVisProp->SetVectorParameterValue(FName(TEXT("ButtonColor")), FLinearColor(0.6f, 0.44f, .04f, 1.0f)); //Set the color of the button
	visualMesh->SetMaterial(0, ButtonVisProp); //Set the material to the updated color
	FVector loc = GetActorLocation(); //Get the location of the actor
	startingX = loc.X; //Set the starting X position
	startingY = loc.Y; //Set the starting Y position
}

void AInvestConfirmButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isPressed >= 0.0f)
	{
		itemDesc->SetWorldScale3D(FVector(normalScaleText, normalScaleText, normalScaleText));
	}
	else if (shakeVal > 0.0f)
	{
		FVector right = GetActorForwardVector(); //Get the right vector, which in the case of the buttons, is actually the forward vector. It's weird, but that's how the orientation is
		FVector loc = GetActorLocation(); //Get location to get the Z value
		FVector oldLocation = FVector(startingX, startingY, loc.Z); //Make the old location
		right *= FMath::Sin(shakeVal * 20.0f) * 2.5f; //Move right vector along sin wave 
		SetActorLocation(oldLocation + right); //Add the vectors together to get the new location
		shakeVal -= DeltaTime; //Decrement the starting time
		if (shakeVal <= 0.0f)
		{
			shakeVal = -1.0f; //Ensure the shake will be disabled
			SetActorLocation(FVector(startingX, startingY, loc.Z)); //Reset location
		}
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