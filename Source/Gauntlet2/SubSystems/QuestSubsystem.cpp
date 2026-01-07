// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/QuestSubsystem.h"
#include "Data/QuestVisualData.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"

void UQuestSubsystem::TryStartNextQuest()
{
	TArray<FName> Names = QuestTable->GetRowNames();
	
	if (Names.IsEmpty()) return;
	
	int i = 0;
	if (Names.Contains(CurrentQuestName))
	{
		i = Names.IndexOfByKey(CurrentQuestName);
		CurrentQuestName = Names[i + 1];
	}
}

void UQuestSubsystem::CompleteQuest(FName QuestName)
{
	// Trova la riga nella DataTable
	static const FString ContextString(TEXT("QuestContext"));
	FQuestDetailsRow* Row = QuestTable->FindRow<FQuestDetailsRow>(QuestName, ContextString);

	if (Row && !Row->QuestAssets.IsNull())
	{
		// Ottieni il Path del DataAsset tramite il Soft Pointer
		FSoftObjectPath AssetPath = Row->QuestAssets.ToSoftObjectPath();

		// Richiedi il caricamento asincrono
		FStreamableManager& Streamable = UAssetManager::Get().GetStreamableManager();
        
		Streamable.RequestAsyncLoad(AssetPath, FStreamableDelegate::CreateUObject(this, &UQuestSubsystem::OnQuestAssetsLoaded, Row->QuestAssets));
	}
	
	TryStartNextQuest();
}

// Funzione Callback chiamata quando gli asset sono pronti in memoria
void UQuestSubsystem::OnQuestAssetsLoaded(TSoftObjectPtr<UQuestVisualData> LoadedAssetPtr)
{
	UQuestVisualData* Data = LoadedAssetPtr.Get();
	if (Data)
	{
		USoundBase* Sound = Data->VictorySound.LoadSynchronous();
		if (Sound) UGameplayStatics::PlaySound2D(GetWorld(), Sound);

		if (Data->IsLastQuest)
		{
			// Logica per tornare al menu dopo 3 secondi...
			
		}
	}
}
