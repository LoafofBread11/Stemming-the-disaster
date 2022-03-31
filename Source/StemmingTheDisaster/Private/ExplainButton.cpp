// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplainButton.h"
#include "Kismet/GameplayStatics.h"

AExplainButton::AExplainButton() : AButtonMain() {
	//constructor here
}

void AExplainButton::BeginPlay() {
	AButtonMain::BeginPlay();
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld())); //Get and cast Game Instance
}

void AExplainButton::raiseFlag(){
	flag = 1;
}

void AExplainButton::click() {
	AButtonMain::click();//call base click
	GI->SetCurrentAction("EXPLAIN");//
	raiseFlag();
}