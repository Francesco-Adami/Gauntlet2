// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Bullet.h"

#include "Gauntlet2Character.h"
#include "SubSystems/ObjectPoolerSubsystem.h"

// Sets default values
ACPP_Bullet::ACPP_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
	OP_SubSystem = GetGameInstance()->GetSubsystem<UObjectPoolerSubsystem>();
}

void ACPP_Bullet::Move(float DeltaTime)
{
	FVector Displacement = BulletDir * BulletSpeed * DeltaTime;

	FHitResult HitResult;
    
	// Muoviamo il proiettile con sweep (collisione attiva)
	AddActorWorldOffset(Displacement, true, &HitResult);

	// Se bBlockingHit è true, abbiamo sbattuto contro qualcosa (muro o player)
	if (HitResult.bBlockingHit)
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor)
		{
			// Verifichiamo se abbiamo colpito un Character (il Player o un nemico)
			AGauntlet2Character* HitCharacter = Cast<AGauntlet2Character>(HitActor);

			if (HitCharacter)
			{
				// Calcoliamo la direzione del contraccolpo.
				// Usiamo la direzione del proiettile + un po' di spinta verso l'alto (Z)
				// per staccare il personaggio dal suolo (attrito) e farlo volare via meglio.
				FVector LaunchDirection = BulletDir;
				LaunchDirection.Z = 0.2f; // Aggiunge un leggero arco verso l'alto
                
				FVector FinalForce = LaunchDirection * KnockbackForce;

				// LaunchCharacter è il metodo migliore per spostare i Character in Unreal
				// I booleani 'true, true' significano: sovrascrivi la velocità attuale (XY e Z)
				HitCharacter->LaunchCharacter(FinalForce, true, true);
				
				// ritorno il proiettile alla pool
				FObjectPoolDeactivateData Data;
				NativeDeactivate(Data);
				TimeElapsed = 0.0f;
			}
		}
	}
}

// Called every frame
void ACPP_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Move(DeltaTime);

	TimeElapsed += DeltaTime;
	if (TimeElapsed > TimeDuration)
	{
		FObjectPoolDeactivateData Data;
		NativeDeactivate(Data);
		TimeElapsed = 0.0f;
	}
}

void ACPP_Bullet::NativeDeactivate(FObjectPoolDeactivateData Data)
{
	IObjectPoolInterface::NativeDeactivate(Data);

	FVector Location = Data.ObjectPoolReturnTransform.GetLocation();
	FRotator Rotation = Data.ObjectPoolReturnTransform.Rotator();
	
	SetActorLocationAndRotation(Location, Rotation);

	// return to pool
	OP_SubSystem->ReturnObjectToPool(GetClass(), this);
	SetActorTickEnabled(false);
}

