// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DoorArtifact.h"

// Sets default values
ACPP_DoorArtifact::ACPP_DoorArtifact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_DoorArtifact::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_DoorArtifact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_DoorArtifact::NativeActivate(AActor* Interactor)
{
	IActivatable::NativeActivate(Interactor);
	
	Destroy();
}

