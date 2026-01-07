// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Turret.h"

#include "Kismet/GameplayStatics.h"
#include "Classes/CPP_Bullet.h"
#include "SubSystems/ObjectPoolerSubsystem.h"


// Sets default values
ACPP_Turret::ACPP_Turret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 1. Creazione del componente
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));

	// 2. Impostazione come Root Component (opzionale ma consigliato per oggetti fisici)
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void ACPP_Turret::BeginPlay()
{
	Super::BeginPlay();
	
	OP_SubSystem = GetGameInstance()->GetSubsystem<UObjectPoolerSubsystem>();
	OP_SubSystem->AddPool(Bullet); // crea la pool di proiettili (di base 30 unità)
	
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	IsActive = true;
	
	if (MeshComponent)
	{
		MaterialInstance = MeshComponent->CreateDynamicMaterialInstance(0);
		UE_LOG(LogTemp, Warning, TEXT("Dynamic Material Instance - CREATED"))
	}
	
	ChangeColor(ActivatedMat);
}

void ACPP_Turret::NativeActivate(AActor* Interactor)
{
	IActivatable::NativeActivate(Interactor);
	
	SetActive(false);
}

// Called every frame
void ACPP_Turret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	GEngine->AddOnScreenDebugMessage(
		1,
		0.0f,
		FColor::Green,
		FString::Printf(TEXT("IsActive: %s"), IsActive ? TEXT("True") : TEXT("False"))
	);
	if (!IsActive) return;
	
	if (Player)
	{
		const bool bCanSee = CanSeeTarget(Player);
		
		GEngine->AddOnScreenDebugMessage(
			2,
			0.0f,
			FColor::Green,
			FString::Printf(TEXT("Can See? %s"), bCanSee ? TEXT("True") : TEXT("False"))
		);

		// --- DEBUG VISIVO ---
		// Se lo vedo: Verde. Se non lo vedo: Rosso.
		FColor DebugColor = bCanSee ? FColor::Green : FColor::Red;
        
		// Disegna il cono in tempo reale nell'editor
		DrawDebugCone(
			GetWorld(),
			GetActorLocation(),
			GetActorForwardVector(),
			ViewDistance,
			FMath::DegreesToRadians(ViewAngle * 0.5f), // Converte angolo in radianti (metà cono)
			FMath::DegreesToRadians(ViewAngle * 0.5f), 
			12, // Risoluzione del cerchio
			DebugColor,
			false, 
			-1.0f, 
			0, 
			5.0f
		);
		
		if (bCanSee)
		{
			FireCooldown += DeltaTime;
			if (FireCooldown >= (1 / FireRate))
			{
				FireCooldown = 0.0f;
				TScriptInterface<IObjectPoolInterface> Tmp = OP_SubSystem->GetObjectFromPool(Bullet);
				
				FObjectPoolActivateData Data;
				
				Data.ObjectPoolTransform = FirePoint * GetActorTransform();
				Data.ProjectileDir = Player->GetActorLocation() - (FirePoint.GetLocation() + GetActorLocation());
				Data.ProjectileDir.Normalize();
				
				Tmp->Activate(Data);
			}
		}
	}
	else
	{
		// provo a riprendermelo
		Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
}

void ACPP_Turret::SetActive(bool Active)
{
	if (Active)
	{
		OnActivated();
	}
	else
	{
		OnDeactivated();
	}
}

void ACPP_Turret::OnActivated()
{
	// ritorna a cercare il player
	IsActive = true;
	ChangeColor(ActivatedMat);
}

void ACPP_Turret::OnDeactivated()
{
	IsActive = false;
	ChangeColor(DeactivatedMat);
	
	FTimerHandle TimerHandle_Fire;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_Fire,
		[this]()
		{
			SetActive(true);
		},
		5.0f,
		false
	);
}

void ACPP_Turret::ChangeColor(FColor NewColor)
{
	if (MaterialInstance)
	{
		MaterialInstance->SetVectorParameterValue("Color", NewColor);
	}
}

bool ACPP_Turret::CanSeeTarget(AActor* TargetActor) const
{
	if (!TargetActor) return false;
	
	FVector TurretLocation = GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();
	FVector ToTarget = (TargetLocation - TurretLocation);
    
	// Controllo DISTANZA
	float DistanceSquared = ToTarget.SizeSquared();
	if (DistanceSquared > (ViewDistance * ViewDistance))
	{
		return false; // Troppo lontano
	}
	ToTarget.Normalize();

	float DotResult = FVector::DotProduct(GetActorForwardVector(), ToTarget);
    
	float HalfAngleRadians = FMath::DegreesToRadians(ViewAngle * 0.5f);
	float AngleThreshold = FMath::Cos(HalfAngleRadians);

	if (DotResult >= AngleThreshold)
	{
		// OSTACOLI
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			TurretLocation,
			TargetLocation,
			ECC_Visibility, // Canale di visibilità
			QueryParams
		);
		
		if (bHit && HitResult.GetActor() == TargetActor)
		{
			return true; // Trovato
		}
	}

	return false;
}
