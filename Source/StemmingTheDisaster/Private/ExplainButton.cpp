// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplainButton.h"
#include "Kismet/GameplayStatics.h"

AExplainButton::AExplainButton() : AButtonMain() {
	//constructor here
}

void AExplainButton::BeginPlay() {
	Super::BeginPlay();
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld())); //Get and cast Game Instance
}

void AExplainButton::raiseFlag(){
	flag = 1;
}

void AExplainButton::click() {
	Super::click();//call base click
	GI->SetCurrentAction("EXPLAIN"); //Set to Explain, may be removed in future and done in Narrator to avoid giving button a copy of the game instance.
}