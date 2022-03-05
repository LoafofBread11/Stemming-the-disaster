// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class STEMMINGTHEDISASTER_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	bool debugMode = false; //Debug mode, decorated with EditAnywhere so that it can be toggled in editor

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* base; //Base Component

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* camera; //Camera Component

	UFUNCTION()
	void AddMouseX(float axis); //Function for translating mouse x movements to camera control

	UFUNCTION()
	void AddMouseY(float axis); //Function for translating mouse y movements to camera control

	UFUNCTION()
	FHitResult Hitscan(); //Function that fires a hit scan beam

	UFUNCTION()
	void Interact(); //Function that fires the hit scan beam, and depending on what it collides with, calls different functions.

	UPROPERTY(VisibleAnywhere)
	FString lookingAtText;

	UFUNCTION()
	FString GetLookingAtText();

	//Create a pointer to the game instance here, will need to cast it in the constructor

};
