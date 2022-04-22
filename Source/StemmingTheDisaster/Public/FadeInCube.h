// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FadeInCube.generated.h"

UCLASS()
class STEMMINGTHEDISASTER_API AFadeInCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFadeInCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* cube; //Static mesh for cube fade out

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* cubeMI; //Material Instance for the cube

	UPROPERTY(VisibleAnywhere)
	float fadeInValue = 1.0f; //Current value of the fade out

};
