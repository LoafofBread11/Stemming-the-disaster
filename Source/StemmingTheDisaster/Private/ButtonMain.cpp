// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonMain.h"

// Sets default values
AButtonMain::AButtonMain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	visualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Button"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ButtonMain(TEXT("/Game/StaticMeshes/ButtonCentered.ButtonCentered"));
	if (ButtonMain.Succeeded())
	{
		visualMesh->SetStaticMesh(ButtonMain.Object);
	}
	RootComponent = visualMesh;

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->SetupAttachment(visualMesh);
}

// Called when the game starts or when spawned
void AButtonMain::BeginPlay()
{
	Super::BeginPlay();
	myScale = GetActorScale3D();
}

// Called every frame
void AButtonMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isPressed >= 0.0f)
	{
		isPressed += DeltaTime;
		myScale.Y = .5 + (cos(PI * isPressed) / 2);
		
		SetActorScale3D(myScale);
	}
	if (isPressed >= 1.0f)
	{
		myScale.Y = 1.0f;
		SetActorScale3D(myScale);
		isPressed = -1.0f;
	}
}

//virtual click function 
void AButtonMain::click()
{
	isPressed = 0.0f;
}

void AButtonMain::setText(FText text)
{
	Text->SetText(text);
}

