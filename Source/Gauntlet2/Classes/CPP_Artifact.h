// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseInteractable.h"
#include "CPP_Artifact.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAUNTLET2_API ACPP_Artifact : public ACPP_BaseInteractable
{
	GENERATED_BODY()
	
public:
	virtual void NativeInteract(AActor* Interactor) override;
};
