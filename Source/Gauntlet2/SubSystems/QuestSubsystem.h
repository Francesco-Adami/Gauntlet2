// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "QuestSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FQuestDetailsRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<AActor> ObjectiveTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 RequiredItems;

	// ------------------------------------------------------
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals")
	// TSoftObjectPtr<class UNiagaraSystem> VictoryVFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<class USoundBase> VictorySound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TSoftObjectPtr<class UPrimaryDataAsset> QuestRewardData;
};

/**
 * 
 */
UCLASS()
class GAUNTLET2_API UQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UDataTable* QuestTable;

public:
	UFUNCTION(BlueprintCallable)
	void StartQuest(FName QuestName);
};
