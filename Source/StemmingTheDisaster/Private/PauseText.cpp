// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseText.h"

// Sets default values
APauseText::APauseText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	pauseText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Pause Menu"));
	RootComponent = pauseText;
	pauseText->SetHorizontalAlignment(EHTA_Center);
	pauseText->SetText("Game Paused");
}

// Called when the game starts or when spawned
void APauseText::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APauseText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

