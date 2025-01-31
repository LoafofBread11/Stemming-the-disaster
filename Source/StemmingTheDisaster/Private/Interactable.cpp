// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "SD_GameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = VisualMesh;
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Sends interactable data to game instance
void AInteractable::SendInteractableData() {

	USD_GameInstance* GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GI->SetInteractableData(FText::FromString(textName), FText::FromString(textDescription));
	for (int i = 0; i < relevantCareers.Num(); i++)
	{
		GI->scoreInteractable(relevantCareers[i], 2); //Add 2 points to an interactable, we might change this
	}
}

