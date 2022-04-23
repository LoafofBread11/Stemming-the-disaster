// Fill out your copyright notice in the Description page of Project Settings.


#include "StartButton.h"

AStartButton::AStartButton() : ADestinationButton()
{

}

void AStartButton::BeginPlay()
{
	Super::BeginPlay();
	ButtonVisProp->SetVectorParameterValue(FName(TEXT("ButtonColor")), FLinearColor(0.42f, 0.05f, .68f, 1.0f));
	visualMesh->SetMaterial(0, ButtonVisProp);
}

void AStartButton::raiseFlag()
{
	//SET THE SIMULATION HERE
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (mapName != "" && (GI->GetCurrentAction() != "DONE"))
	{
		GI->StartSimulator(simulationName);
		GI->ChangeMap(mapName);
	}
}