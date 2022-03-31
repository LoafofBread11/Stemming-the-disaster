// Fill out your copyright notice in the Description page of Project Settings.


#include "Narrator.h"

// Sets default values
ANarrator::ANarrator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = VisualMesh;
}

// Called when the game starts or when spawned
void ANarrator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANarrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANarrator::StartTalk() {

}

void ANarrator::EndTalk() {

}

void ANarrator::CreateInvestMenu() {

}

void ANarrator::CreateMainMenu() {

}

void ANarrator::CreateTravelMenu() {

}

void ANarrator::CreateExplainMenu() {

}

void ANarrator::ClearMenu() {
	int i;

	for (i = 0; i < buttons.Num(); i++) {
		buttons.RemoveAt(i);
	}

	buttons.Empty();
}

void ANarrator::HandleFlags() {

}