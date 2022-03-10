// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Math/UnrealMathUtility.h"
#include "ButtonMain.generated.h"

UCLASS()
class STEMMINGTHEDISASTER_API AButtonMain : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AButtonMain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void click();

	UFUNCTION()
		void setText(FText text);

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* visualMesh;

	UPROPERTY(VisibleAnywhere)
		UTextRenderComponent* Text;

	UPROPERTY(VisibleAnywhere)
		float isPressed = -1.0f;

	FVector myScale;
};