// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Activatable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActivatable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAUNTLET2_API IActivatable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// general version to call in c++
	void Activate(AActor* Interactor) { NativeActivate(Interactor); }

	// activate to implement in c++
	virtual void NativeActivate(AActor* Interactor)
	{
		UObject* Object = Cast<UObject>(this);
		Execute_BP_Activate(Object, Interactor);
	}

	// ===== Functions to implement =====
	// activate to implement in blueprint
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Activatable")
	void BP_Activate(AActor* Interactor);
};
