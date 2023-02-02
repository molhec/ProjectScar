// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"

#include <string>

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"


//////////////////////////////////////////////////////////////////////////
// AProjectScarCharacter

APlayerCharacter::APlayerCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	TriggerForInteraction = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger for Interaction"));
	TriggerForInteraction->SetupAttachment(GetCapsuleComponent());

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	TriggerForInteraction->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlapTriggerInteractions);
	TriggerForInteraction->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEndTriggerInteractions);

	DialogInstance = CreateWidget<UUserWidget>(GetWorld(), DialogWidgetObj);
	DialogInstance->AddToViewport();

	UDialogWidget* dialogWidget = Cast<UDialogWidget>(DialogInstance);

	if(dialogWidget != nullptr)
	{
		dialogWidget->SetDialogPanelVisibility(false);
	}

	CurrentInfectionValue = InfectionValueToDie;

	OnStartDialog.AddDynamic(this, &APlayerCharacter::ShowDialog);
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	CurrentInfectionValue -= DeltaSeconds;

	UDialogWidget* dialogWidget = Cast<UDialogWidget>(DialogInstance);

	if(dialogWidget != nullptr)
	{
		dialogWidget->SetSliderValue(CurrentInfectionValue/InfectionValueToDie);
	}

	GEngine->AddOnScreenDebugMessage(2, DeltaSeconds, FColor::Red, "Current Infection Value: " + FString::SanitizeFloat(CurrentInfectionValue));
}

//////////////////////////////////////////////////////////////////////////// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TryToInteract);
	}
}


void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::TryToInteract(const FInputActionValue& Value)
{
	if(ObjNearToInteract != nullptr)
	{
		Cast<IIInteractable>(ObjNearToInteract)->Interact(this);
	}
}

void APlayerCharacter::ShowDialog(FString stringToShow)
{
	OnStartDialog.Broadcast(stringToShow);
	UDialogWidget* dialogWidget = Cast<UDialogWidget>(DialogInstance);

	if(dialogWidget != nullptr)
	{
		dialogWidget->SetDialogPanelVisibility(true);
		dialogWidget->SetDialog(stringToShow);
	}
}

void APlayerCharacter::ShowFlashback(UTexture2D* TextureFlashback)
{
	UDialogWidget* dialogWidget = Cast<UDialogWidget>(DialogInstance);

	if(dialogWidget != nullptr)
	{
		dialogWidget->ShowFlashback(TextureFlashback, GetController());
	}
}

void APlayerCharacter::HideDialog()
{
	UDialogWidget* dialogWidget = Cast<UDialogWidget>(DialogInstance);

	if(dialogWidget != nullptr)
	{
		dialogWidget->SetDialogPanelVisibility(false);
	}
}

void APlayerCharacter::CureInfection(float InfectionToCure)
{
	CurrentInfectionValue += InfectionToCure;

	if(CurrentInfectionValue > InfectionValueToDie)
		CurrentInfectionValue = InfectionValueToDie;
}

void APlayerCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool APlayerCharacter::GetHasRifle()
{
	return bHasRifle;
}

void APlayerCharacter::OnBeginOverlapTriggerInteractions(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(ObjNearToInteract != nullptr) return;

	IIInteractable* interactuable = Cast<IIInteractable>(OtherActor);
	
	if(interactuable != nullptr)
	{
		ObjNearToInteract = OtherActor;
		interactuable->StartFocus();
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Green, TEXT("Interactuable Obj in range"));
	}
}

void APlayerCharacter::OnOverlapEndTriggerInteractions(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == ObjNearToInteract)
	{
		Cast<IIInteractable>(ObjNearToInteract)->EndFocus();
		ObjNearToInteract = nullptr;
	}
}


