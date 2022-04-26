// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeOutTravelCube.h"

// Sets default values
AFadeOutTravelCube::AFadeOutTravelCube()
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
void AFadeOutTravelCube::BeginPlay()
{
	Super::BeginPlay();
	cubeMI = UMaterialInstanceDynamic::Create(cube->GetMaterial(0), this); //Create the Material Instance
	cubeMI->SetScalarParameterValue(FName(TEXT("OpacityScale")), 0); //Set the opacity scale on the MI
	cube->SetMaterial(0, cubeMI); //Set the material
	
}

// Called every frame
void AFadeOutTravelCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	fadeOutValue += DeltaTime * 2.0f; //Increase the fadeout value
	cubeMI->SetScalarParameterValue(FName(TEXT("OpacityScale")), fadeOutValue); //Set the opacity scale on the MI
	cube->SetMaterial(0, cubeMI); //Set the material
	if (fadeOutValue >= 1.0 && mapName != "") //If we are fully opaque and we have a map
	{
		USD_GameInstance* GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if(GI->GetCurrentAction() != "DONE")
			UGameplayStatics::OpenLevel((UObject*)GI, FName(mapName));
	}
}

