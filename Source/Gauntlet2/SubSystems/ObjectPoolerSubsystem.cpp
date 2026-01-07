// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/ObjectPoolerSubsystem.h"

void UObjectPoolerSubsystem::AddPool(TSubclassOf<AActor> ClassToPool, int32 InitialSize)
{
	if (!GetWorld()) return;
	// Controlli
	if (!IsValid(ClassToPool)) return;
	if (!ClassToPool->ImplementsInterface(UObjectPoolInterface::StaticClass())) return;
	
	
	FObjectPool TempPool;

	FActorSpawnParameters SpawnParameters;
	// SpawnParameters.spa

	for (int32 i = 0; i < InitialSize; i++)
	{
		
		AActor* ActorRef = GetWorld()->SpawnActor<AActor>(
			ClassToPool,
			FVector(0, 0, 100),
			FRotator(0, 0, 0),
			SpawnParameters
		);

		TempPool.UsablePoolingObjects.AddUnique(ActorRef);
		
		ActorRef->SetActorTickEnabled(false);
		ActorRef->SetActorHiddenInGame(true);
		ActorRef->SetActorEnableCollision(false);
	}
		
	ObjectPoolMap.Add(ClassToPool, TempPool);
	
}

TScriptInterface<IObjectPoolInterface> UObjectPoolerSubsystem::GetObjectFromPool(TSubclassOf<AActor> ClassToPool)
{
	TScriptInterface<IObjectPoolInterface> Actor = nullptr;
	
	if (!GetWorld()) return Actor;
	// Controlli
	if (!IsValid(ClassToPool)) return Actor;
	if (!ObjectPoolMap.Contains(ClassToPool)) return Actor;
	
	FObjectPool* PoolObject = ObjectPoolMap.Find(ClassToPool);

	if (PoolObject->UsablePoolingObjects.IsEmpty())
	{
		Actor = GetWorld()->SpawnActor<AActor>(ClassToPool);
	}
	else
	{
		Actor = PoolObject->UsablePoolingObjects[0];
		PoolObject->UsablePoolingObjects.RemoveAt(0);
	}

	PoolObject->ActivePoolingObjects.AddUnique(Actor);
	// Actor->SetActorHiddenInGame(false);
	return Actor;
}

void UObjectPoolerSubsystem::ReturnObjectToPool(TSubclassOf<AActor> ClassToPool, TScriptInterface<IObjectPoolInterface> ActorToReturn)
{
	if (!GetWorld()) return;
	// Controlli
	if (!IsValid(ClassToPool)) return;
	if (!ObjectPoolMap.Contains(ClassToPool)) return;

	FObjectPool* PoolObject = ObjectPoolMap.Find(ClassToPool);

	if (!PoolObject->ActivePoolingObjects.Contains(ActorToReturn))
	{
		UE_LOG(LogTemp, Warning, TEXT("Non era negli active"))
	}

	PoolObject->ActivePoolingObjects.Remove(ActorToReturn);
	PoolObject->UsablePoolingObjects.AddUnique(ActorToReturn);

	// ActorToReturn->SetActorHiddenInGame(true);
}

int UObjectPoolerSubsystem::GetUsablePoolSize(TSubclassOf<AActor> ClassToPool)
{
	if (!GetWorld()) return -1;
	if (!ObjectPoolMap.Contains(ClassToPool)) return -1;

	FObjectPool* PoolObject = ObjectPoolMap.Find(ClassToPool);

	return PoolObject->UsablePoolingObjects.Num();
}

int UObjectPoolerSubsystem::GetActivePoolSize(TSubclassOf<AActor> ClassToPool)
{
	if (!GetWorld()) return -1;
	if (!ObjectPoolMap.Contains(ClassToPool)) return -1;

	FObjectPool* PoolObject = ObjectPoolMap.Find(ClassToPool);

	return PoolObject->ActivePoolingObjects.Num();
}