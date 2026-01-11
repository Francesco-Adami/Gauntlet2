// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gauntlet2Character.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CPP_GI_Checkpoints.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAUNTLET2_API UCPP_GI_Checkpoints : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void RespawnAtCheckpoint(FTransform Transform, AGauntlet2Character* Character);
};
