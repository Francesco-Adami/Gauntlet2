// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseInteractable.h"

#include "Gauntlet2Character.h"

// Sets default values
ACPP_BaseInteractable::ACPP_BaseInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. Creazione del componente
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));

	// 2. Impostazione come Root Component (opzionale ma consigliato per oggetti fisici)
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void ACPP_BaseInteractable::BeginPlay()
{
	Super::BeginPlay();

	if (MeshComponent)
	{
		MaterialInstance = MeshComponent->CreateDynamicMaterialInstance(0);
		UE_LOG(LogTemp, Warning, TEXT("Dynamic Material Instance - CREATED"))
	}
}

// Called every frame
void ACPP_BaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_BaseInteractable::NativeInteract(AActor* Interactor)
{
	IInteractable::NativeInteract(Interactor);

	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Red,
		TEXT("LEVER - Interacted")
	);

	IsActivated = !IsActivated;

	UpdateObjectState(IsActivated ? ActivatedMat : DeactivatedMat);
}

void ACPP_BaseInteractable::UpdateObjectState(FColor Color)
{
	if (MeshComponent)
	{
		// Cambia il valore del parametro "StatusColor" nel materiale
		MaterialInstance->SetVectorParameterValue("Color", Color);
	}
}

void ACPP_BaseInteractable::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (AGauntlet2Character* Char = Cast<AGauntlet2Character>(OtherActor))
	{
		Char->SetInteractable(this);
	}
}

void ACPP_BaseInteractable::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (AGauntlet2Character* Char = Cast<AGauntlet2Character>(OtherActor))
	{
		if (Char->GetInteractable() == this)
		{
			Char->SetInteractable(nullptr);
		}
	}
}
