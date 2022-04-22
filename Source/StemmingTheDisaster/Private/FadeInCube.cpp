// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeInCube.h"

// Sets default values
AFadeInCube::AFadeInCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Disappearing Cube")); //Declare a sub object
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeObj(TEXT("/Game/StaticMeshes/FlippedBox.FlippedBox")); //Find the cube we are using
	if (cubeObj.Succeeded()) //If it was successful
	{
		cube->SetStaticMesh(cubeObj.Object); //Set the static mesh
	}
	cube->SetRelativeScale3D(FVector(.5f, .5f, .5f)); //Shrink the cube to the camera
	RootComponent = cube; //Set the cube as the root component

}

// Called when the game starts or when spawned
void AFadeInCube::BeginPlay()
{
	Super::BeginPlay();
	cubeMI = UMaterialInstanceDynamic::Create(cube->GetMaterial(0), this); //Create the Material Instance
	cubeMI->SetScalarParameterValue(FName(TEXT("OpacityScale")), 1); //Set the opacity scale on the MI
	cube->SetMaterial(0, cubeMI); //Set the material
	FVector loc = GetActorLocation(); //Get the actor location
	loc.Z += 150.0f; //Move the actor up
	SetActorLocation(loc); //Set the location
	
}

// Called every frame
void AFadeInCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	fadeInValue -= DeltaTime * 2.0f; //Increase the fadeout value
	cubeMI->SetScalarParameterValue(FName(TEXT("OpacityScale")), fadeInValue); //Set the opacity scale on the MI
	cube->SetMaterial(0, cubeMI); //Set the material
	if (fadeInValue <= 0.0f) //If we are fully Clear
	{
		Destroy(); //The purpose has been fufilled
	}

}

