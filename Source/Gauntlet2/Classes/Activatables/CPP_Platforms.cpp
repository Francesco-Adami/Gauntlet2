// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Platforms.h"

#include "SceneProxies/ReflectionCaptureProxy.h"

// Sets default values
ACPP_Platforms::ACPP_Platforms()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PivotRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PivotRoot"));
	RootComponent = PivotRoot;
}

// Called when the game starts or when spawned
void ACPP_Platforms::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 0; i < NumberOfPlatforms; i++)
	{
		UStaticMeshComponent* NewMesh = NewObject<UStaticMeshComponent>(this);
		if (NewMesh)
		{
			if (Platform)
			{
				NewMesh->SetStaticMesh(Platform);
			}

			NewMesh->RegisterComponent();
			NewMesh->AttachToComponent(PivotRoot, FAttachmentTransformRules::KeepRelativeTransform);
        
			UMaterialInstanceDynamic* DynMat = NewMesh->CreateDynamicMaterialInstance(0, PlatformMat);
			if (DynMat)
			{
				DynMat->SetVectorParameterValue("Color", FLinearColor(DeactivatedMat));
				DynamicMaterials.Add(DynMat);
			}

			PlatformMeshes.Add(NewMesh);
		}
	}
	
	AdjustPlatforms();
}

// Called every frame
void ACPP_Platforms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsActive) return;

	CurrentAngle += RotationSpeed * DeltaTime;
	CurrentAngle = FMath::Fmod(CurrentAngle, 360.0f);

	AdjustPlatforms();
}

void ACPP_Platforms::NativeActivate(AActor* Interactor)
{
	IActivatable::NativeActivate(Interactor);
	bIsActive = !bIsActive;
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Platforms Activated"));

	for (int i = 0; i < DynamicMaterials.Num(); ++i)
	{
		DynamicMaterials[i]->SetVectorParameterValue("Color", bIsActive ? ActivatedMat : DeactivatedMat);
	}
}

void ACPP_Platforms::AdjustPlatforms()
{
	// piazzo le piattaforme in modo omogeneo nella circonferenza
	float AngleStep = 360.f / NumberOfPlatforms;

	for (int32 i = 0; i < PlatformMeshes.Num(); i++)
	{
		float Degree = CurrentAngle + (i * AngleStep);
		float Rad = FMath::DegreesToRadians(Degree);
		FVector NewLocation = FVector(FMath::Cos(Rad) * OrbitRadius, FMath::Sin(Rad) * OrbitRadius, 0.f);
        
		PlatformMeshes[i]->SetRelativeLocation(NewLocation);
	}
}
