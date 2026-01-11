// Copyright Epic Games, Inc. All Rights Reserved.

#include "Gauntlet2Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Gauntlet2.h"
#include "Interfaces/Interactable.h"
#include "SubSystems/QuestSubsystem.h"

AGauntlet2Character::AGauntlet2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AGauntlet2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGauntlet2Character::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AGauntlet2Character::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGauntlet2Character::Look);

		// ===== Interacting =====
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AGauntlet2Character::Interact);

		// ===== Pause Game =====
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AGauntlet2Character::Interact);
	}
	else
	{
		UE_LOG(LogGauntlet2, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AGauntlet2Character::BeginPlay()
{
	Super::BeginPlay();
}

void AGauntlet2Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetActorLocation().Z < -200.0f)
	{
		if (!HasArtifact())
		{
			SetActorLocation(FVector::ZeroVector);
		}
		else
		{
			Respawn();
		}
	}
}

void AGauntlet2Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AGauntlet2Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AGauntlet2Character::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AGauntlet2Character::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AGauntlet2Character::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AGauntlet2Character::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AGauntlet2Character::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("Interact called"));
	if (!IsValid(Interactable.GetObject()))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.f,
			FColor::Blue,
			TEXT("Nessun interagibile")
		);
		return;
	}

	Interactable->Interact(this);
	GEngine->AddOnScreenDebugMessage(
		-1,
		2.f,
		FColor::Blue,
		TEXT("Interagito con: " + Interactable.GetObject()->GetName())
	);
}

void AGauntlet2Character::PauseGame()
{
	GetWorld()->GetWorldSettings()->TimeDilation = 0.0f;

	// UnpauseGame è nel WBP_PauseMenuUI
}

void AGauntlet2Character::SetInteractable(TScriptInterface<IInteractable> Value)
{
	this->Interactable = Value;
}
