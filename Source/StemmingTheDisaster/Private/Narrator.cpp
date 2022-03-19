// Fill out your copyright notice in the Description page of Project Settings.


#include "Narrator.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANarrator::ANarrator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = VisualMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> vmObj(TEXT("/Game/StaticMeshes/NarratorStaticMesh/Narrator_Model.Narrator_Model"));
	if (vmObj.Succeeded())
	{
		VisualMesh->SetStaticMesh(vmObj.Object);
	}
}

// Called when the game starts or when spawned
void ANarrator::BeginPlay()
{
	Super::BeginPlay();
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld())); //Get and cast Game Instance
	
}

// Called every frame
void ANarrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANarrator::StartTalk() {
	GI->SetCurrentAction("NARRATOR_MAIN");
	CreateMainMenu();
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

}

void ANarrator::HandleFlags() {

}