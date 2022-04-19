// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplainButton.h"
#include "Kismet/GameplayStatics.h"

AExplainButton::AExplainButton() : AButtonMain() {
	//constructor here
}

void AExplainButton::BeginPlay() {
	Super::BeginPlay();
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld())); //Get and cast Game Instance
	ButtonVisProp->SetVectorParameterValue(FName(TEXT("ButtonColor")), FLinearColor(0.3f, 0.11f, .52f, 1.0f));
	visualMesh->SetMaterial(0, ButtonVisProp);
}

void AExplainButton::raiseFlag(){
	flag = 1;
}

void AExplainButton::click() {
	Super::click();//call base click
}