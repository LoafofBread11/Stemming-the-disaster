// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonMain.h"

// Sets default values
AButtonMain::AButtonMain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	buttonScale = 1;
	isPressed = -1;
	visualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Button"));
}

// Called when the game starts or when spawned
void AButtonMain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isPressed != -1)
	{
		isPressed += DeltaTime;
		buttonScale = .5 + (cos(PI * isPressed) / 2);
		myScale.Y = buttonScale;
		SetActorScale3D(myScale);
	}
	else if (isPressed >= 1)
	{
		myScale.Y = 1;
		SetActorScale3D(myScale);
		isPressed = -1;
	}
}

//virtual click function 
void AButtonMain::click()
{
	isPressed = 0;
}

void AButtonMain::setText(FText text)
{
	Text->SetText(text);
}

