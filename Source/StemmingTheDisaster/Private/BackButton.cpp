// Fill out your copyright notice in the Description page of Project Settings.


#include "BackButton.h"
ABackButton::ABackButton() : AButtonMain()
{

}

void ABackButton::BeginPlay()
{
	Super::BeginPlay();
}

void ABackButton::raiseFlag()
{
	flag = 1;
	
}
