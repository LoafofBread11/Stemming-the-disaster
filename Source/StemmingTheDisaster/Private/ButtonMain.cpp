// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonMain.h"

// Sets default values
AButtonMain::AButtonMain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	visualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Button"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ButtonMain(TEXT("/Game/StaticMeshes/ButtonCentered.ButtonCentered"));
	if (ButtonMain.Succeeded())
	{
		visualMesh->SetStaticMesh(ButtonMain.Object);
	}
	RootComponent = visualMesh;

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->SetupAttachment(RootComponent);
	Text->SetRelativeLocationAndRotation(FVector(0.0f, 31.0f, 0.0f), FRotator(0.0f, 90.0f, 0.0f)); //Realign text so it's on top of the button
	Text->SetHorizontalAlignment(EHTA_Center); //Align the Horizontal Center of the text to be the center, not the left
}

// Called when the game starts or when spawned
void AButtonMain::BeginPlay()
{
	Super::BeginPlay();
	myScale = GetActorScale3D(); //Get the scale of the actor
	normalScale = myScale.Y; //Store the Y of the scale
	ButtonVisProp = UMaterialInstanceDynamic::Create(visualMesh->GetMaterial(0), this);
	ButtonVisProp->SetScalarParameterValue(FName(TEXT("ButtonGlow")), 0);
	//ButtonVisProp->SetVectorParameterValue(FName(TEXT("ButtonColor")), FLinearColor(0.0f, 1.0f, .5f, 1.0f));
	visualMesh->SetMaterial(0, ButtonVisProp);
}

// Called every frame
void AButtonMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isPressed >= 0.0f)
	{
		isPressed += (DeltaTime * 2);
		myScale.Y = (normalScale / 4) + (FMath::Abs(cos(PI * isPressed)) * 3 * normalScale / 4); //Scale the button relative to itself on an absolute cosine wave, producing a smooth animation
		SetActorScale3D(myScale);
		Text->SetWorldScale3D(FVector(myScale.X, normalScale, myScale.Z)); //Set the absolute scale of the text so that it remains visible
	}
	if (isPressed >= 1.0f)
	{
		myScale.Y = normalScale; //Ensure the scale of Y is reset back to normal
		SetActorScale3D(myScale); //Reset the actor scale
		Text->SetWorldScale3D(FVector(myScale)); //Reset the text scale
		isPressed = -1.0f;
		raiseFlag();
	}
	if (isHighlighted > 0.0f)
	{
		isHighlighted -= (DeltaTime * 2.0f);
		if (isHighlighted < 0.0f)
		{
			isHighlighted = -1.0f;
			ButtonVisProp->SetScalarParameterValue(FName(TEXT("ButtonGlow")), 0);
		}
		else
			ButtonVisProp->SetScalarParameterValue(FName(TEXT("ButtonGlow")), isHighlighted);
		visualMesh->SetMaterial(0, ButtonVisProp);
	}
}

//virtual click function 
void AButtonMain::click()
{
	if(isPressed < 0.0f) //If the button isn't already clicked
		isPressed = 0.0f; //Push the button
}

void AButtonMain::setText(FText text)
{
	Text->SetText(text);
}

void AButtonMain::raiseFlag()
{
	//Raise your flags here
}