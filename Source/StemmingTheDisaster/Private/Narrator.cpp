// Fill out your copyright notice in the Description page of Project Settings.


#include "Narrator.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANarrator::ANarrator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = VisualMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> vmObj(TEXT("/Game/StaticMeshes/NarratorStaticMesh/Narrator_Model.Narrator_Model"));
	if (vmObj.Succeeded())
	{
		VisualMesh->SetStaticMesh(vmObj.Object);
	}
}

// Called when the game starts or when spawned
void ANarrator::BeginPlay()
{
	Super::BeginPlay();
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld())); //Get and cast Game Instance
	
}

// Called every frame
void ANarrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANarrator::StartTalk() {
	GI->SetCurrentAction("NARRATOR_MAIN");
	CreateMainMenu();
}

void ANarrator::EndTalk() {

}

void ANarrator::CreateInvestMenu() {

}

void ANarrator::CreateMainMenu() {

}

void ANarrator::CreateTravelMenu() {

}

void ANarrator::CreateExplainMenu() {

}

void ANarrator::ClearMenu() {
	int i;

	for (i = 0; i < buttons.Num(); i++) {
		buttons[i]->Destroy(); //Destroy the button
	}

	buttons.Empty(); //Empty the list
}

void ANarrator::HandleFlags() {
	for (int i = 0; i > buttons.Num(); i++)
	{
		if (buttons[i]->flag > 0)
		{
			ABackButton* BB = Cast<ABackButton>(buttons[i]);
			if (BB)
			{
				//Deal with Back Button Here
			}
			else
			{
				ADestinationButton* DB = Cast<ADestinationButton>(buttons[i]);
				if (DB)
				{
					//Left in in case we decide to move the functionality of changing menus to the narrator, maybe for visual flair
				}
				else
				{
					AExplainButton* EB = Cast<AExplainButton>(buttons[i]);
					if (EB)
					{
						//Deal with Explanation button here. We can load the sound and necessary things in here. 
					}
					else
					{
						AInvestConfirmButton* CB = Cast<AInvestConfirmButton>(buttons[i]);
						if (CB)
						{
							//Deal with Investment here
						}
						else
						{
							AMenuButton* MB = Cast<AMenuButton>(buttons[i]);
							if (MB)
							{
								//Deal with Menu Buttons here
							}
							else
							{
								//Something went wrong, or a regular button was pressed.
							}
						}
					}
				}
			}
		}
	}
}