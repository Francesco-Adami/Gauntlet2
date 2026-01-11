// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Activatable.h"
#include "CPP_Platforms.generated.h"

UCLASS()
class GAUNTLET2_API ACPP_Platforms : public AActor, public IActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Platforms();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> DynamicMaterials;
	
	// Material instance of Deactivated Lever status
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	FColor DeactivatedMat;

	// Material instance of Activated Lever status
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	FColor ActivatedMat;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMesh* Platform;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInterface* PlatformMat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void NativeActivate(AActor* Interactor) override;
	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* PivotRoot;

	// Array dinamico di Mesh per le N piattaforme 
	UPROPERTY(VisibleAnywhere)
	TArray<UStaticMeshComponent*> PlatformMeshes;

	UPROPERTY(EditAnywhere, Category = "Orbit Settings")
	int32 NumberOfPlatforms = 3;

	UPROPERTY(EditAnywhere, Category = "Orbit Settings")
	float OrbitRadius = 300.f;

	UPROPERTY(EditAnywhere, Category = "Orbit Settings")
	float RotationSpeed = 50.f;

	// Stato iniziale: Ferme 
	bool bIsActive = false;
	float CurrentAngle = 0.f;
	
	void AdjustPlatforms();
};
