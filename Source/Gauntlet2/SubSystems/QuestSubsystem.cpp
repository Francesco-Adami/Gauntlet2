// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/QuestSubsystem.h"
#include "Data/QuestVisualData.h"
#include "DevSettings/DevSettings.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	const UDevSettings* Settings = GetDefault<UDevSettings>();
    
	if (Settings && Settings->QuestDataTable.ToSoftObjectPath().IsValid())
	{
		QuestTable = Settings->QuestDataTable.LoadSynchronous();
	}
	
	CurrentQuestIndex = -1;
}

void UQuestSubsystem::CompleteQuest()
{
	if (!QuestTable) return;
	
	GetNextQuestName();

	// 1. Troviamo la riga nella DataTable
	static const FString ContextString(TEXT("Quest Lookup"));
	FQuestDetailsRow* Row = QuestTable->FindRow<FQuestDetailsRow>(QuestTitle, ContextString);

	if (Row)
	{
		if (Row->QuestAssets.IsValid())
		{
			OnQuestCompletedDelegate.Broadcast(Row->QuestTitle, Row->QuestAssets.Get());
		}
		else
		{
			if (UAssetManager* Manager = UAssetManager::GetIfInitialized())
			{
				// lista di cosa caricare
				TArray<FSoftObjectPath> AssetsToLoad;
				AssetsToLoad.Add(Row->QuestAssets.ToSoftObjectPath());

				// caricamento asincrono
				CurrentLoadHandle = Manager->GetStreamableManager().RequestAsyncLoad(
					AssetsToLoad, 
					FStreamableDelegate::CreateUObject(
					this, 
					&UQuestSubsystem::OnQuestAssetsLoaded, 
					Row->QuestTitle, 
					Row->QuestAssets)
				);
			}
		}
	}
}

// Funzione Callback (chiamata quando gli asset sono pronti in memoria)
void UQuestSubsystem::OnQuestAssetsLoaded(FName QuestName, TSoftObjectPtr<UQuestVisualData> AssetPtr)
{
	UQuestVisualData* LoadedData = AssetPtr.Get();

	if (LoadedData)
	{
		OnQuestCompletedDelegate.Broadcast(QuestName, LoadedData);
	}
    
	CurrentLoadHandle.Reset();
}

void UQuestSubsystem::GetNextQuestName()
{
	static const FString ContextString(TEXT("Quest Lookup"));
	TArray<FName> AllQuests = QuestTable->GetRowNames();
	
	CurrentQuestIndex += 1;
	if (CurrentQuestIndex >= AllQuests.Num()) return;
	
	QuestTitle = AllQuests[CurrentQuestIndex];
}
