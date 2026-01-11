// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Exit.h"

#include "Gauntlet2Character.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystems/QuestSubsystem.h"

void ACPP_Exit::NativeInteract(AActor* Interactor)
{
	AGauntlet2Character* MyChar = Cast<AGauntlet2Character>(Interactor);
	if (!MyChar) return;
	
	if (MyChar->HasArtifact())
	{
		AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACPP_Artifact::StaticClass());
		ACPP_Artifact* Artifact = Cast<ACPP_Artifact>(FoundActor);
		PlaceArtifact(Artifact);
		
		Super::NativeInteract(Interactor);
		EndGame();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Red,
		TEXT("YOU DON'T HAVE THE ARTIFACT")
		);
	}
}

void ACPP_Exit::PlaceArtifact_Implementation(ACPP_Artifact* Artifact)
{
	FDetachmentTransformRules DetachRules(FDetachmentTransformRules::KeepWorldTransform);
	Artifact->DetachFromActor(DetachRules);
	
	Artifact->SetActorLocation(this->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f));
}

void ACPP_Exit::EndGame_Implementation()
{
	GetGameInstance()->GetSubsystem<UQuestSubsystem>()->SetCurrentQuestIndex(-1);
}
