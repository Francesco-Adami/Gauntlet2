// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "QuestSubsystem.generated.h"

class UQuestVisualData;

USTRUCT(BlueprintType)
struct FQuestDetailsRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestTitle;

	// Invece di avere i VFX qui, puntiamo al DataAsset che li contiene
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TSoftObjectPtr<UQuestVisualData> QuestAssets;
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
	
	FName CurrentQuestName;
	
	void TryStartNextQuest();

public:	
	UFUNCTION(BlueprintCallable)
	void CompleteQuest(FName QuestName);
	
	void OnQuestAssetsLoaded(TSoftObjectPtr<UQuestVisualData> LoadedAssetPtr);
};
