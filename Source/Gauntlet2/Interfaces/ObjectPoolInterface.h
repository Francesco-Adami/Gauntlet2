// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectPoolInterface.generated.h"

USTRUCT(BlueprintType)
struct FObjectPoolActivateData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Object Pool Data")
	FTransform ObjectPoolTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Object Pool Data")
	FVector ProjectileDir;
	
};

USTRUCT(BlueprintType)
struct FObjectPoolDeactivateData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Object Pool Data")
	FTransform ObjectPoolReturnTransform;
	
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObjectPoolInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAUNTLET2_API IObjectPoolInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// general version to call in c++
	void Activate(const FObjectPoolActivateData& Data) { NativeActivate(Data); }
	void Deactivate(const FObjectPoolDeactivateData& Data) { NativeDeactivate(Data); }

	// ===== Functions to implement =====
	// activate to implement in blueprint
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Object Pool")
	void BP_Activate(FObjectPoolActivateData Data);

	// activate to implement in c++
	virtual void NativeActivate(FObjectPoolActivateData Data)
	{
		UObject* Object = Cast<UObject>(this);
		Execute_BP_Activate(Object, Data);
	}

	// =======================================================================
	// deactivate to implement in blueprint
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Object Pool")
	void BP_Deactivate(FObjectPoolDeactivateData Data);

	// deactivate to implement in c++
	virtual void NativeDeactivate(FObjectPoolDeactivateData Data)
	{
		UObject* Object = Cast<UObject>(this);
		Execute_BP_Deactivate(Object, Data);
	}
};
