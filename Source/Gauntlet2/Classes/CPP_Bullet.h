// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ObjectPoolInterface.h"
#include "SubSystems/ObjectPoolerSubsystem.h"
#include "CPP_Bullet.generated.h"

UCLASS(Blueprintable)
class GAUNTLET2_API ACPP_Bullet : public AActor, public IObjectPoolInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float KnockbackForce = 600.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet")
	float TimeDuration = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float BulletSpeed;
	
	float TimeElapsed = 0.0f;
	FVector BulletDir;
	
	// FUNCTIONS
	void Move(float DeltaTime);

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UObjectPoolerSubsystem* OP_SubSystem;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetDirection(const FVector& NewDir) { BulletDir = NewDir; }
	
	virtual void NativeDeactivate(FObjectPoolDeactivateData Data) override;
};
