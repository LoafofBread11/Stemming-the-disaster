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
				//clear menu
				ClearMenu();
				//call game instance and get current action save in FSTRING
				FString temp = GI->GetCurrentAction();
				//see if FSTRING = Narrator_main As scene and start talk, set to idel
				if (temp == "NARRATOR_MAIN")
				{
					GI->SetCurrentAction("IDLE");
				}
				else
				{
					GI->SetCurrentAction("NARRATOR_MAIN");
					CreateMainMenu();
					//create main menu
				}
				// if not, set to narrator main and create main menu
				//return out
				return;
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
							
							//Clear menu
							ClearMenu();

							//Gets current action from game instance
							FString action = GI->GetCurrentAction();

							//If the game instance is idle and ready to do something
							if (action == "IDLE")
							{
								//Set the current action to invest.
								GI->SetCurrentAction("INVEST");

								//Call make investment for the button's item.
								//Will let us know if the investment is successful or not.
								if (GI->MakeInvestment(CB->item))
								{
									//Investment was successful.
								}
								else
								{
									//Investment failed.
								}
							}
							//Sets current action back to idle then returns.
							GI->SetCurrentAction("IDLE");
							return;
						}
						else
						{
							AMenuButton* MB = Cast<AMenuButton>(buttons[i]);
							if (MB)
							{
								//Deal with Menu Buttons here
								//delete already existing buttons
								ClearMenu();
								//compare FSRING to invest travel explain, compare then create menus
								if (buttons[i]->textString == "INVEST")
								{
									CreateInvestMenu();
								}
								else if (buttons[i]->textString == "EXPLAIN")
								{
									CreateExplainMenu();
								}
								else if (buttons[i]->textString == "TRAVEL")
								{
									CreateTravelMenu();
								}
								return;
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