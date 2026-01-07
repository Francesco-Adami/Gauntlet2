#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundBase.h"
#include "QuestVisualData.generated.h"

/**
 * Questo Data Asset conterrà i riferimenti soft agli asset pesanti
 */
UCLASS(BlueprintType)
class GAUNTLET2_API UQuestVisualData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> VictorySound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	bool IsLastQuest = false;
};