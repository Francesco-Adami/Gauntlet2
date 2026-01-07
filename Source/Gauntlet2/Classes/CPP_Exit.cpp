// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Exit.h"

#include "Gauntlet2Character.h"

void ACPP_Exit::NativeInteract(AActor* Interactor)
{
	AGauntlet2Character* MyChar = Cast<AGauntlet2Character>(Interactor);
	if (!MyChar) return;
	
	if (MyChar->HasArtifact())
	{
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
