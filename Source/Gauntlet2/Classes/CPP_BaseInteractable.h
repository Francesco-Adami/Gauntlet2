// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Interfaces/Activatable.h"
#include "CPP_BaseInteractable.generated.h"

UCLASS()
class GAUNTLET2_API ACPP_BaseInteractable : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_BaseInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsActivated = false;

	// Mesh component pointer
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	// Material instance of Deactivated Lever status
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	FColor DeactivatedMat;

	// Material instance of Activated Lever status
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	FColor ActivatedMat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInstanceDynamic* MaterialInstance;
	
	UPROPERTY(EditInstanceOnly, Category = "Interaction")
	TArray<TScriptInterface<IActivatable>> Activatables;

	// Update Material Instance Color
	UFUNCTION(BlueprintCallable)
	void UpdateObjectState(FColor Color);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NativeInteract(AActor* Interactor) override;

};
