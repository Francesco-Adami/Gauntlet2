// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Artifact.h"

#include "Gauntlet2Character.h"

void ACPP_Artifact::NativeInteract(AActor* Interactor)
{
	AGauntlet2Character* MyCharacter = Cast<AGauntlet2Character>(Interactor);
	
	if (!MyCharacter) return;
	if (MyCharacter->HasArtifact()) return;
	
	Super::NativeInteract(Interactor);
	
	// solo l'artefatto:
	// si attacca al corpo del player

	if (MyCharacter)
	{
		// Prendiamo la mesh dell'artefatto
		UStaticMeshComponent* ArtifactMesh = Cast<UStaticMeshComponent>(GetRootComponent());
        
		if (ArtifactMesh)
		{
			// disabilito tutte le collisioni per evitare problemi quando viene attaccato al player
			ArtifactMesh->SetSimulatePhysics(false);
			ArtifactMesh->SetCollisionProfileName(TEXT("NoCollision"));
		}

		// --- ATTACCO AL POLAYER ---
		FName SocketName = TEXT("ArtifactSocket");

		this->AttachToComponent(
			MyCharacter->GetMesh(), 
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
			SocketName
		);

		// aggiorna lo stato del player: bHasArtifact -> true
		MyCharacter->CollectArtifact();
		
		// MyCharacter->SetInteractable(nullptr);
	}
}
