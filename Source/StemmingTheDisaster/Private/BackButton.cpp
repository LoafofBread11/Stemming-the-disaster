// Fill out your copyright notice in the Description page of Project Settings.


#include "BackButton.h"
ABackButton::ABackButton() : AButtonMain()
{

}

void ABackButton::BeginPlay()
{
	Super::BeginPlay();
	ButtonVisProp->SetVectorParameterValue(FName(TEXT("ButtonColor")), FLinearColor(0.19f, 0.20f, .20f, 1.0f));
	visualMesh->SetMaterial(0, ButtonVisProp);
}

void ABackButton::raiseFlag()
{
	flag = 1;
	
}
