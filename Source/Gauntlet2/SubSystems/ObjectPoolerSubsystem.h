// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ObjectPoolInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ObjectPoolerSubsystem.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FObjectPool
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Object Pooler Struct")
	TArray<TScriptInterface<IObjectPoolInterface>> UsablePoolingObjects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Object Pooler Struct")
	TArray<TScriptInterface<IObjectPoolInterface>> ActivePoolingObjects;
};

UCLASS()
class GAUNTLET2_API UObjectPoolerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Object Pool SubSystem")
	TMap<TSubclassOf<AActor>, FObjectPool> ObjectPoolMap;

	// Add a pool of objects
	UFUNCTION(BlueprintCallable, Category = "Object Pool SubSystem")
	void AddPool(TSubclassOf<AActor> ClassToPool, int32 InitialSize = 30);

	UFUNCTION(BlueprintCallable, Category = "Object Pool SubSystem")
	TScriptInterface<IObjectPoolInterface> GetObjectFromPool(TSubclassOf<AActor> ClassToPool);

	UFUNCTION(BlueprintCallable, Category = "Object Pool SubSystem")
	void ReturnObjectToPool(TSubclassOf<AActor> ClassToPool, TScriptInterface<IObjectPoolInterface> ActorToReturn);

	// Helpers
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Object Pool SubSystem")
	int GetUsablePoolSize(TSubclassOf<AActor> ClassToPool);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Object Pool SubSystem")
	int GetActivePoolSize(TSubclassOf<AActor> ClassToPool);
	
};
