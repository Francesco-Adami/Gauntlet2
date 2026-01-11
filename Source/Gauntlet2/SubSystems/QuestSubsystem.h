// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "QuestSubsystem.generated.h"

class UQuestVisualData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestCompletedSignature, FName, QuestName, UQuestVisualData*, LoadedVisuals);

USTRUCT(BlueprintType)
struct FQuestDetailsRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestTitle;

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
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	int CurrentQuestIndex;
	FName QuestTitle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	UDataTable* QuestTable;
	
	FName CurrentQuestName;
	TSharedPtr<struct FStreamableHandle> CurrentLoadHandle;

public:	
	UFUNCTION(BlueprintCallable)
	void CompleteQuest();
	
	UPROPERTY(BlueprintAssignable, Category = "Quest System")
	FOnQuestCompletedSignature OnQuestCompletedDelegate;
	
	void OnQuestAssetsLoaded(FName QuestName, TSoftObjectPtr<UQuestVisualData> AssetPtr);
	
	void GetNextQuestName();
	void SetCurrentQuestIndex(int Index) { CurrentQuestIndex = Index; }
};
