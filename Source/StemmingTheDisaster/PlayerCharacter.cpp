// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Public/Interactable.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Public/ButtonMain.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Narrator.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	base = CreateDefaultSubobject<USceneComponent>(TEXT("Base")); //Setup the base component. This allows for the component to be moved around
	RootComponent = base; //Set the base as the root component

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); //Setup the camera component
	camera->SetupAttachment(base); //Attach the camera to the base component
	camera->SetRelativeLocation(FVector(0.0f, 0.0f, 125.0f)); //Position the camera 125u above the base component
	camera->bUsePawnControlRotation = true; //Allow for controller rotation inputs to manipulate the camera
	camera->bLockToHmd = true; //Allow for HMD inputs to manipulate the camera

	//Create UI Widgets
	valueWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("3D Value Displays"));
	static ConstructorHelpers::FClassFinder<UUserWidget> valueObj(TEXT("/Game/UIWidgets/ValueDisplays"));
	if (valueObj.Succeeded())
	{
		valueWidget->SetWidgetClass(valueObj.Class);
	}
	valueWidget->SetupAttachment(camera);
	valueWidget->SetRelativeLocation(FVector(80.0f, 20.0f, 2.5f));
	valueWidget->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	valueWidget->SetRelativeScale3D(FVector(1.0f, .075f, .075f));
	valueWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	valueWidget->SetBlendMode(EWidgetBlendMode::Transparent);

	reticleWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("3D Reticle"));
	
	static ConstructorHelpers::FClassFinder<UUserWidget> retObj(TEXT("/Game/UIWidgets/Reticle"));
	if (retObj.Succeeded())
	{
		reticleWidget->SetWidgetClass(retObj.Class);
	}
	reticleWidget->SetupAttachment(camera);
	reticleWidget->SetRelativeLocation(FVector(80.0f, 0.0f, 0.0f));
	reticleWidget->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	reticleWidget->SetRelativeScale3D(FVector(1.0f, .1f, .1f));
	reticleWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	reticleWidget->SetBlendMode(EWidgetBlendMode::Transparent);
	

	lAtWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("3D Looking At Text"));
	
	static ConstructorHelpers::FClassFinder<UUserWidget> latObj(TEXT("/Game/UIWidgets/LookingAtText"));
	if (latObj.Succeeded())
	{
		lAtWidget->SetWidgetClass(latObj.Class);
	}
	lAtWidget->SetupAttachment(camera);
	lAtWidget->SetRelativeLocation(FVector(80.0f, 0.0f, -2.5f));
	lAtWidget->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	lAtWidget->SetRelativeScale3D(FVector(1.0f, .075f, .075f));
	lAtWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	lAtWidget->SetBlendMode(EWidgetBlendMode::Transparent);
	

	interactableName = CreateDefaultSubobject<UWidgetComponent>(TEXT("3D Interactable Text Name"));
	static ConstructorHelpers::FClassFinder<UUserWidget> intName(TEXT("/Game/UIWidgets/InteractableNameWidget"));
	if (intName.Succeeded())
	{
		interactableName->SetWidgetClass(intName.Class);
	}
	interactableName->SetupAttachment(camera);
	interactableName->SetRelativeLocation(FVector(80.0f, -20.0f, -1.0f));
	interactableName->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	interactableName->SetRelativeScale3D(FVector(1.0f, .075f, .075f));
	interactableName->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	interactableName->SetBlendMode(EWidgetBlendMode::Transparent);

	interactableText = CreateDefaultSubobject<UWidgetComponent>(TEXT("3D Interactable Text Description"));
	static ConstructorHelpers::FClassFinder<UUserWidget> intText(TEXT("/Game/UIWidgets/InteractableTextW"));
	if (intText.Succeeded())
	{
		interactableText->SetWidgetClass(intText.Class);
	}
	interactableText->SetupAttachment(camera);
	interactableText->SetRelativeLocation(FVector(80.0f, -13.5f, 1.0f));
	interactableText->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	interactableText->SetRelativeScale3D(FVector(1.0f, .05f, .05f));
	interactableText->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	interactableText->SetBlendMode(EWidgetBlendMode::Transparent);
	interactableText->SetDrawSize(FVector2D(1000.0f, 1000.0f));

	captionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("3D Caption Text"));
	static ConstructorHelpers::FClassFinder<UUserWidget> capObj(TEXT("/Game/UIWidgets/Captions"));
	if (capObj.Succeeded())
	{
		captionWidget->SetWidgetClass(capObj.Class);
	}
	captionWidget->SetupAttachment(camera);
	captionWidget->SetRelativeLocation(FVector(80.0f, 0.0f, -3.0f));
	captionWidget->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	captionWidget->SetRelativeScale3D(FVector(1.0f, .075f, .075f));
	captionWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	pauseMenu = CreateDefaultSubobject<UWidgetComponent>(TEXT("3D Pause Menu"));
	static ConstructorHelpers::FClassFinder<UUserWidget> pauseObj(TEXT("/Game/UIWidgets/PauseMenu"));
	if (pauseObj.Succeeded())
	{
		pauseMenu->SetWidgetClass(pauseObj.Class);
	}
	pauseMenu->SetupAttachment(camera);
	pauseMenu->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AutoPossessPlayer = EAutoReceiveInput::Player0; //Set the pawn to take input from the player
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GI = Cast<USD_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld())); //Get and cast Game Instance
	if (GI->getInVR()) //If we are in VR
	{
		FVector loc = GetActorLocation(); //Get location of actor
		//loc.Z += 150; //Raise location by 150 units
		SetActorLocation(loc); //Set the location
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GI->GetCurrentAction());
		if (GI->GetCurrentAction() == "RESULTS" || GI->GetCurrentAction() == "START") //If we're in the results room
		{
			valueWidget->SetRelativeScale3D(FVector(0.0f)); //Hide the components anyway
			//Don't hide the reticle, it is still useful
			lAtWidget->SetRelativeScale3D(FVector(0.0f));
			captionWidget->SetRelativeScale3D(FVector(0.0f));
			interactableName->SetRelativeScale3D(FVector(0.0f));
			interactableText->SetRelativeScale3D(FVector(0.0f));
		}
	}
	else
	{
		valueWidget->SetRelativeScale3D(FVector(0.0f)); //Hide the components
		reticleWidget->SetRelativeScale3D(FVector(0.0f));
		lAtWidget->SetRelativeScale3D(FVector(0.0f));
		captionWidget->SetRelativeScale3D(FVector(0.0f));
		interactableName->SetRelativeScale3D(FVector(0.0f));
		interactableText->SetRelativeScale3D(FVector(0.0f));
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Not in VR"));
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult OutHit = Hitscan(); //Fire the beam, see if the object is looking at anything
	if (OutHit.bBlockingHit) //If something collided
	{
		if (OutHit.GetComponent()->GetAttachmentRootActor() != NULL) //Make sure we hit something and not a volume
		{
			AInteractable* collideInt = Cast<AInteractable>(OutHit.GetActor()); //Attempt to cast the object to an interactable
			if (collideInt) //If successful
			{
				lookingAtText = collideInt->textName; //Set the text to the interactable
			}
			else
			{
				ANarrator* collideNar = Cast<ANarrator>(OutHit.GetActor()); //Cast to the narrator
				if (collideNar) //If successful
				{
					lookingAtText = "Narrator"; //Set text to Narrator
				}
				else
				{
					lookingAtText = ""; //Set looking at text to nothing, then check rest of conditions
					AButtonMain* collideBut = Cast<AButtonMain>(OutHit.GetActor()); //Check if looking at button
					if (collideBut) //If successful
					{
						collideBut->isHighlighted = 1.0f; //Highlight the button
					}
				}
			}
		}
		else
		{
			lookingAtText = ""; //Set looking at text to nothing
		}
	}
	else //If no text was successful
	{
		lookingAtText = "";
	}

	FString current = GI->GetCurrentAction();
	if (current == "RESULTS" || current == "DONE" || current == "START")
		done = true;

	if (!done) //If not done yet
	{
		float time = GI->getRemainingTime(); //Get the remaining time
		time -= DeltaTime; //Subtract the delta time from it
		GI->setRemainingTime(time); //Set the new time
		if (time <= 0.0f) //If no more time remains
		{
			done = true; //Then we are done
			GI->SetCurrentAction("DONE"); //Sets current action to done
			GI->setRemainingTime(3.0f); //Allow 3 seconds of done time
			GI->EndSimulator(); //Calculate the results
		}
	}
	else if (GI->GetCurrentAction() == "DONE")
	{
		float time = GI->getRemainingTime(); //Get the remaining time
		time -= DeltaTime; //Subtract the delta time from it
		GI->setRemainingTime(time); //Set the new time
		if (time <= 0.0f) //If no more time remains
		{
			GI->SetCurrentAction("RESULTS"); //Set proper action
			GI->ChangeMap("ResultsMap"); //Go to results map
		}
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MouseX", this, &APlayerCharacter::AddMouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &APlayerCharacter::AddMouseY);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);

}

void APlayerCharacter::AddMouseX(float axis)
{
	AddControllerYawInput(axis); //Take in mouse x input and translate it to the camera's yaw
}

void APlayerCharacter::AddMouseY(float axis)
{
	AddControllerPitchInput(axis * -1); //Take in mouse y input, invert it, and translate it to the camera's pitch
}

FHitResult APlayerCharacter::Hitscan()
{
	FHitResult OutHit; //Create the FHitResult
	FVector startLoc = camera->GetComponentLocation(); //Determine the start location of the beam
	FVector Forward = camera->GetForwardVector(); //Determine the forward vector (The direction of the camera as represented by a 3 value vector)
	startLoc += (Forward * 15); //Advance the start location by the forward vector * 15, done so the beam is not interrupted by the camera
	FVector endLoc = (Forward * 10000) + startLoc; //Determine the end location
	FCollisionQueryParams colpar; //Create collision parameters. Needed for the function call, but we do not need to do anything with them
	if(debugMode) //If we are in debug mode
		DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Green, false, 1, 0, 1); //Draw the line represented by the trace
	GetWorld()->LineTraceSingleByChannel(OutHit, startLoc, endLoc, ECC_Visibility, colpar); //Fire the hitscan

	return OutHit; //Return the results
}

void APlayerCharacter::Interact()
{
	FString ca = GI->GetCurrentAction();
	if (ca == "INTERACTABLE") //If we are currently already looking at an interactable
	{
		GI->SetCurrentAction("IDLE"); //Clear the state
		return; //Exit the function
	}
	FHitResult OutHit = Hitscan(); //Call the hitscan function to determine what is being looked at, if anything
	if (OutHit.bBlockingHit && OutHit.GetComponent()->GetAttachmentRootActor() != NULL)
	{
		AInteractable* collideInt = Cast<AInteractable>(OutHit.GetActor()); //Attempt to cast the object to an interactable
		if (collideInt && ca == "IDLE") //If successful
		{
			GI->SetCurrentAction("INTERACTABLE"); //Set the current action
			collideInt->SendInteractableData();
			return;
		}

		AButtonMain* collideBut = Cast<AButtonMain>(OutHit.GetActor());
		if (collideBut)
		{
			collideBut->click();
			return;
		}

		ANarrator* collideNar = Cast<ANarrator>(OutHit.GetActor());
		if (collideNar && GI->GetCurrentAction() == "IDLE") //If we are in idle and we talked to the narrator
		{
			collideNar->StartTalk(); //Begin talking to narrator
			return;
		}
	}
}

FString APlayerCharacter::GetLookingAtText()
{
	return lookingAtText;
}

