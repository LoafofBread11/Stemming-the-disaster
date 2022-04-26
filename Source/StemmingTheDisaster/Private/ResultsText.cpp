// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultsText.h"
#include "SD_GameInstance.h"

// Sets default values
AResultsText::AResultsText()
{
	PrimaryActorTick.bCanEverTick = false; //The actor does not need to tick. It just needs to get information as soon as it is created, and then simply display that information
	resultsText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Results Text"));
	RootComponent = resultsText; //Set the text as the base component
	resultsText->SetHorizontalAlignment(EHTA_Center); //Align the Horizontal Center of the text to be the center

}

// Called when the game starts or when spawned
void AResultsText::BeginPlay()
{
	Super::BeginPlay();
	USD_GameInstance* GI = Cast<USD_GameInstance>(GetWorld()->GetGameInstance()); //Get the game instance
	if (GI) //If the game instance was successfully retrieved
	{
		if (resultIndex > -1 && GI->results.Num() > resultIndex) //If the index we are looking up is not negative AND there is an element for our index
			resultsText->SetText(FText::FromString(GI->results[resultIndex])); //Set the text to be the the string at the index of our selected result index
		else
			resultsText->SetText(""); //Index is invalid, blank out the text
	}
	else
		resultsText->SetText(""); //Error occured, blank out the text
	
}

// Called every frame
void AResultsText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

