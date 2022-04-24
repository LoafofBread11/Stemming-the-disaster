// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "ResultsText.generated.h"

UCLASS()
class STEMMINGTHEDISASTER_API AResultsText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResultsText();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* resultsText; //Text that will display the results necessary

	UPROPERTY(EditAnywhere)
	int resultIndex = -1; //Index of the Game Instance's results that the component will try to read


};
