// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuButton.h"
AMenuButton::AMenuButton() : AButtonMain()
{

}

void AMenuButton::BeginPlay()
{
	Super::BeginPlay();
}

void AMenuButton::raiseFlag()
{
	if (textString == "Invest")
		flag = 1;
	else if (textString == "Travel")
		flag = 2;
	else if (textString == "Explain")
		flag = 3;
	else
		flag = 0;
}