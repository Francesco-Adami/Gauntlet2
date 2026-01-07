// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_NewLever.h"

void ACPP_NewLever::NativeInteract(AActor* Interactor)
{
	Super::NativeInteract(Interactor);
	
	// solo leve
	for (auto Activatable : Activatables)
	{
		if (Activatable)
		{
			Activatable.GetInterface()->NativeActivate(this);
		}
	}
}
