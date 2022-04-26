// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinationButton.h"

ADestinationButton::ADestinationButton() : AButtonMain()
{

}

void ADestinationButton::BeginPlay()
{
	Super::BeginPlay();
	ButtonVisProp->SetVectorParameterValue(FName(TEXT("ButtonColor")), FLinearColor(0.18f, 0.46f, .51f, 1.0f));
	visualMesh->SetMaterial(0, ButtonVisProp);
}

void ADestinationButton::raiseFlag()
{
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (mapName != "" && (GI->GetCurrentAction() != "DONE"))
	{
		GI->ChangeMap(mapName);
	}
}
