// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Public/Interactable.h"
#include "DrawDebugHelpers.h"

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

	AutoPossessPlayer = EAutoReceiveInput::Player0; //Set the pawn to take input from the player
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
				lookingAtText = collideInt->textName;
			}
			else
			{
				lookingAtText = ""; //Set looking at text to nothing, then check rest of conditions
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

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MouseX", this, &APlayerCharacter::AddMouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &APlayerCharacter::AddMouseY);

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
	FVector endLoc = (Forward * 1000) + startLoc; //Determine the end location
	FCollisionQueryParams colpar; //Create collision parameters. Needed for the function call, but we do not need to do anything with them
	if(debugMode) //If we are in debug mode
		DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Green, false, 1, 0, 1); //Draw the line represented by the trace
	GetWorld()->LineTraceSingleByChannel(OutHit, startLoc, endLoc, ECC_Visibility, colpar); //Fire the hitscan

	return OutHit; //Return the results
}

void APlayerCharacter::Interact()
{
	//TO DO
	//Get the game instance's current action
	//If the action is looking at an interactable, set the action to idle, and exit the function
	FHitResult OutHit = Hitscan(); //Call the hitscan function to determine what is being looked at, if anything
	//TO DO
	//Determine what object is interrupting the beam via casting
	//Take appropriate action depending on which cast is successful
	//For interactables, ensure that the action is idle before activating them
}

FString APlayerCharacter::GetLookingAtText()
{
	return lookingAtText;
}