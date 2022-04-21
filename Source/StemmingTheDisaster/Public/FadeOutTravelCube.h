// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "SD_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "FadeOutTravelCube.generated.h"

UCLASS()
class STEMMINGTHEDISASTER_API AFadeOutTravelCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFadeOutTravelCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* cube; //Static mesh for cube fade in

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* cubeMI; //Material Instance for the cube

	UPROPERTY(VisibleAnywhere)
	float fadeOutValue = 0.0f; //Current value of the fade in

	UPROPERTY(VisibleAnywhere)
	FString mapName; //The name of the map that will be traveled to upon completion



};
