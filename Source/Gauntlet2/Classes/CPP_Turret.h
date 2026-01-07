// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Activatable.h"
#include "CPP_Turret.generated.h"

class UObjectPoolerSubsystem;
class ACPP_Bullet;

UCLASS(BlueprintType, Blueprintable)
class GAUNTLET2_API ACPP_Turret : public AActor, public  IActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Turret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void NativeActivate(AActor* Interactor) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UObjectPoolerSubsystem* OP_SubSystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	float FireRate = 3.0f; // 3 proiettili al secondo

	// Material instance of Deactivated Lever status
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	FColor DeactivatedMat;

	// Material instance of Activated Lever status
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	FColor ActivatedMat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInstanceDynamic* MaterialInstance;
	
	float FireCooldown = 0.0f;

public:	
	// Mesh component pointer
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget = true))
	FTransform FirePoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TSubclassOf<AActor> Bullet;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Setter IsActive
	void SetActive(bool Active);
	
	void OnActivated();
	void OnDeactivated();
	
	void ChangeColor(FColor NewColor);
	
	// Vision Logic
	UPROPERTY()
	AActor* Player;
	
	UPROPERTY(EditAnywhere, Category = "AI Vision")
	float ViewDistance = 1500.0f; // 15m

	UPROPERTY(EditAnywhere, Category = "AI Vision", meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float ViewAngle = 90.0f; // -45° to 45°

	bool CanSeeTarget(AActor* TargetActor) const;
};
