// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Gauntlet2Character.generated.h"

class IInteractable;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AGauntlet2Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	// ===== INTERACT =====
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InteractAction;

	// ===== PAUSE GAME =====
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* PauseAction;

public:

	/** Constructor */
	AGauntlet2Character();	

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, Category="Interactable", meta=(AllowPrivateAccess = "true"))
	TScriptInterface<IInteractable> Interactable;
	
	bool bHasArtifact = false;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	/** Handles Interactions */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void Interact();

	/** Handles Pause Game */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void PauseGame();

	/** Handles SetInteractable */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void SetInteractable(TScriptInterface<IInteractable> Value);

	/** Handles SetInteractable */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual TScriptInterface<IInteractable> GetInteractable()
	{
		return this->Interactable;
	}
	
	virtual void CollectArtifact() { bHasArtifact = true; GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Collect Artifact !!")); }
	virtual bool HasArtifact() { return bHasArtifact; }

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

