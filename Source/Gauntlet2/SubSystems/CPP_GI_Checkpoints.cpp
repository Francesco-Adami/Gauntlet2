// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/CPP_GI_Checkpoints.h"

void UCPP_GI_Checkpoints::RespawnAtCheckpoint(FTransform Transform, AGauntlet2Character* Character)
{
	Character->SetActorLocation(Transform.GetLocation());
}
