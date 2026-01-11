// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Artifact.h"
#include "CPP_BaseInteractable.h"
#include "CPP_Exit.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAUNTLET2_API ACPP_Exit : public ACPP_BaseInteractable
{
	GENERATED_BODY()
	
public:
	virtual void NativeInteract(AActor* Interactor) override;
	
	UFUNCTION(BlueprintCallable, BlueprintType, BlueprintNativeEvent)
	void PlaceArtifact(ACPP_Artifact* Artifact);
	
	UFUNCTION(BlueprintCallable, BlueprintType, BlueprintNativeEvent)
	void EndGame();
};
