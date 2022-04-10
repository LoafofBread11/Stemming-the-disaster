// Fill out your copyright notice in the Description page of Project Settings.


#include "Narrator.h"
#include "Sound/SoundCue.h"
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

	explainClip = CreateDefaultSubobject<UAudioComponent>(TEXT("Explain Clip")); //Define voice clip component
	explainClip->SetupAttachment(RootComponent); //Setup attachment
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
	HandleFlags();
	if (GI->GetCurrentAction() == "EXPLAIN") //Check if the narrator is currently explaining something
	{
		voiceTimeRemaining -= DeltaTime; //Subtract the delta time from the voice clip time
 		if (voiceTimeRemaining <= 0.0f) //Check if the time has depleted
		{
			CreateExplainMenu(); //Create the explain menu
			GI->SetCurrentAction("NARRATOR_EXPLAIN"); //Set the correct subaction
		}
	}
}

void ANarrator::StartTalk() {
	FString test = GI->GetCurrentAction();

	if (test == "IDLE") {
		GI->SetCurrentAction("NARRATOR_MAIN");
		CreateMainMenu();
	}
	
}

void ANarrator::EndTalk() {

}

void ANarrator::CreateInvestMenu() {
	GI->SetCurrentAction("NARRATOR_INVEST");
	FVector myLoc = GetActorLocation();
	FRotator myRot = GetActorRotation();
	myRot.Yaw *= 4.0f;

	AButtonMain* newBackButton = GetWorld()->SpawnActor<ABackButton>(ABackButton::StaticClass(), FVector(myLoc.X + 100.0f, myLoc.Y, myLoc.Z - 15.0f), myRot);   // Spawn newBackButton actor for ABackButton
	newBackButton->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f));   // Modify newBackButton scale
	newBackButton->setScale();
	newBackButton->setText(FText::FromString(TEXT("Back")));   // Set newBackButton text

	buttons.Add(newBackButton);   // Add newBackButton to buttons array

	float spawnHeight = 0.0f;
	for (auto It = GI->investmentOptions.CreateConstIterator(); It; ++It)
	{
		AButtonMain* newButton = GetWorld()->SpawnActor<AInvestConfirmButton>(AInvestConfirmButton::StaticClass(), FVector(myLoc.X + 100.0f, myLoc.Y, myLoc.Z + 15.0f + spawnHeight), myRot);
		newButton->SetActorScale3D(FVector(0.375f, 0.25f, 0.25f));   // Modify newButton scale
		newButton->setScale();
		FString cost = "$" + FString::FromInt(It.Value());
		newButton->setText(FText::FromString(cost));
		
		AInvestConfirmButton* IB = Cast<AInvestConfirmButton>(newButton);
		IB->itemDesc->SetText(It.Key());
		IB->item = It.Key();

		buttons.Add(newButton);
		spawnHeight += 30.0f;
	}
}

// Creates invest, travel, explain, menu, and back Buttons
void ANarrator::CreateMainMenu() {
	FVector myLoc = GetActorLocation(); // Stores the actors location and rotation
	FRotator myRot = GetActorRotation();
	myRot.Yaw = myRot.Yaw * 4.0f; // Sets myRot to turn around since buttons were spawning facing the narrator, not player

	AButtonMain* newBackButton = GetWorld()->SpawnActor<ABackButton>(ABackButton::StaticClass(), FVector(myLoc.X + 100.0f, myLoc.Y, myLoc.Z - 15.0f), myRot); // spawns backbutton
	newBackButton->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f)); // Reduces scale
	newBackButton->setScale();
	newBackButton->setText(FText::FromString("Back"));

	AButtonMain* newInvestButton = GetWorld()->SpawnActor<AMenuButton>(AMenuButton::StaticClass(), FVector(myLoc.X + 100.0f, myLoc.Y, myLoc.Z + 75.0f), myRot); // spawns InvestButton
	newInvestButton->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f)); // Reduces scale
	newInvestButton->setScale();
	newInvestButton->setText(FText::FromString("Invest"));

	AButtonMain* newExplainButton = GetWorld()->SpawnActor<AMenuButton>(AMenuButton::StaticClass(), FVector(myLoc.X + 100.0f, myLoc.Y, myLoc.Z + 45.0f), myRot); // Spawns ExplainButton
	newExplainButton->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f)); // Reduces scale
	newExplainButton->setScale();
	newExplainButton->setText(FText::FromString("Explain"));

	AButtonMain* newTravelButton = GetWorld()->SpawnActor<AMenuButton>(AMenuButton::StaticClass(), FVector(myLoc.X + 100.0f, myLoc.Y, myLoc.Z + 15.0f), myRot); // Spawns TravelButton
	newTravelButton->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f)); // Reduces scale
	newTravelButton->setScale();
	newTravelButton->setText(FText::FromString("Travel"));

	// Adds all buttons to the buttons[] array
	buttons.Add(newBackButton);
	buttons.Add(newInvestButton);
	buttons.Add(newExplainButton);
	buttons.Add(newTravelButton);
}

void ANarrator::CreateTravelMenu() {
	GI->SetCurrentAction("NARRATOR_TRAVEL");
	FVector myLoc = GetActorLocation();   // Get actor location and rotation to spawn button
	FRotator myRot = GetActorRotation();
	myRot.Yaw *= 4.0; //Correct face of buttons
	int i = 0;

	AButtonMain* newBackButton = GetWorld()->SpawnActor<ABackButton>(ABackButton::StaticClass(), FVector(myLoc.X + 100.0f, myLoc.Y, myLoc.Z - 15.0f), myRot);   // Spawn newBackButton actor for ABackButton

	newBackButton->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f));   // Modify newBackButton scale
	newBackButton->setScale();
	newBackButton->setText(FText::FromString(TEXT("Back")));   // Set newBackButton text

	buttons.Add(newBackButton);   // Add newBackButton to buttons array


	for (i = 0; i < GI->travelableMaps.Num(); i++) {   // Iterate through travelableMaps array
		AButtonMain* newButton = GetWorld()->SpawnActor<ADestinationButton>(ADestinationButton::StaticClass(), FVector(myLoc.X + 100.0f, myLoc.Y, myLoc.Z + 15.0f + (i * 30.0f)), myRot);   // Spawn newButton actor for ADestinationButton
		
		newButton->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f));   // Modify newButton scale
		newButton->setScale();
		newButton->setText(FText::FromString(GI->mapNameLookup(GI->travelableMaps[i])));   // Set newButton text

		ADestinationButton* DB = Cast<ADestinationButton>(newButton);   // Cast base button to destination
		DB->mapName = GI->travelableMaps[i];   // Set mapName for DB

		buttons.Add(newButton);   // Add newButton to buttons array
	}
}

void ANarrator::CreateExplainMenu() {
	GI->SetCurrentAction("NARRATOR_EXPLAIN");
	FVector myLoc = GetActorLocation();   // Get actor location and rotation to spawn button
	FRotator myRot = GetActorRotation();
	myRot.Yaw *= 4.0; //Correct face of buttons
	int i = 0;

	AButtonMain* newBackButton = GetWorld()->SpawnActor<ABackButton>(ABackButton::StaticClass(), FVector(myLoc.X + 100.0f, myLoc.Y, myLoc.Z - 15.0f), myRot);   // Spawn newBackButton actor for ABackButton

	newBackButton->SetActorScale3D(FVector(0.25f, 0.25f, 0.25f));   // Modify newBackButton scale
	newBackButton->setScale(); //Do scale correction
	newBackButton->setText(FText::FromString(TEXT("Back")));   // Set newBackButton text

	buttons.Add(newBackButton);   // Add newBackButton to buttons array


	for (i = 0; i < GI->dialogueOptions.Num(); i++) {   // Iterate through dialogueOptions array
		AButtonMain* newButton = GetWorld()->SpawnActor<AExplainButton>(AExplainButton::StaticClass(), FVector(myLoc.X + 100.0f, myLoc.Y, myLoc.Z + 15.0f + (i * 30.0f)), myRot);   // Spawn newButton actor for ADestinationButton

		newButton->SetActorScale3D(FVector(0.375f, 0.25f, 0.25f));   // Modify newButton scale
		newButton->setScale(); //Set scale correction
		newButton->setText(FText::FromString(GI->dialogueOptions[i].Key));   // Set newButton text

		AExplainButton* EB = Cast<AExplainButton>(newButton);   // Cast base button to explain
		EB->dialogueCode = GI->dialogueOptions[i].Value;   // Set dialogueCode for EB

		buttons.Add(newButton);   // Add newButton to buttons array
	}
}

void ANarrator::ClearMenu() {
	int i;

	for (i = 0; i < buttons.Num(); i++) {
		buttons[i]->Destroy(); //Destroy the button
	}

	buttons.Empty(); //Empty the list
}

void ANarrator::HandleFlags() {
	for (int i = 0; i < buttons.Num(); i++)
	{
		if (buttons[i]->flag >= 0)
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
						FString code = EB->dialogueCode; //Get the code
						FString location = "/Game/VoiceClips/" + code + "." + code; //Make the location string
						USoundCue* cue = Cast<USoundCue>(StaticLoadObject(USoundCue::StaticClass(), NULL, *location)); //Attempt to load the voice clip
						if (cue) //If the cue load was successful
						{
							explainClip->SetSound(cue);
							voiceTimeRemaining = cue->GetDuration(); //Set the time that the voice clip will play
							explainClip->Play(); //Play the Audio Component
							GI->SetCurrentAction("EXPLAIN"); //Set action to explain, not narrator explain.
							//Check for if a new clip needs to be loaded.
							ClearMenu(); //Remove the buttons while the explanation plays
						}
						return;
					}
					else
					{
						AInvestConfirmButton* CB = Cast<AInvestConfirmButton>(buttons[i]);
						if (CB)
						{
							//Deal with Investment here
							//Call make investment for the button's item.
							//Will let us know if the investment is successful or not.
							if (GI->MakeInvestment(CB->item))
							{
								//Investment was successful.
								ClearMenu(); //Clear menu
								CreateInvestMenu(); //Remake the investment menu, now without the previous investment
							}
							else
							{
								//Investment failed.
							}
							return;
						}
						else
						{
							AMenuButton* MB = Cast<AMenuButton>(buttons[i]);
							if (MB)
							{
								//Deal with Menu Buttons here
								//delete already existing buttons
								FString code = buttons[i]->textString; //Store text string, as the investment menu will be destroyed.
								ClearMenu();
								//compare FSRING to invest travel explain, compare then create menus
								if (code == "Invest")
								{
									CreateInvestMenu();
								}
								else if (code == "Explain")
								{
									CreateExplainMenu();
								}
								else if (code == "Travel")
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