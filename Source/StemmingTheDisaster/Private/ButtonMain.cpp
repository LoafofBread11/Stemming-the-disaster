// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonMain.h"

// Sets default values
AButtonMain::AButtonMain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

//virtual click function 
void AButtonMain::click()
{

}

void AButtonMain::setText(FString text)
{
	Text->SetText(text);
}

