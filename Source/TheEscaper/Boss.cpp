// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EAIControllerBase.h"
#include "Projectile.h"
// Sets default values
ABoss::ABoss()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RotationPivot = CreateDefaultSubobject<USceneComponent>("RotationPivot");
	RotationPivot->SetupAttachment(RootComp);
	
	Muzzle = CreateDefaultSubobject<USceneComponent>("Muzzle");
	Muzzle->SetupAttachment(RotationPivot);

	WheelPivot = CreateDefaultSubobject<USceneComponent>("WheelPivot");
	WheelPivot->SetupAttachment(RotationPivot);
}

bool ABoss::LookAt(AActor* Target, float DeltaTime)
{
	FRotator currentRot = RotationPivot->GetComponentRotation();
	FRotator lookRot = UKismetMathLibrary::FindLookAtRotation(RotationPivot->GetComponentLocation(), Target->GetActorLocation());

	if (currentRot.Equals(lookRot, 1)) 
		return true;

	RotationPivot->SetWorldRotation(FMath::Lerp(currentRot, lookRot, DeltaTime * RotationLerpSpeed));
	return false;
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	RandomRotationSpeed();
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	WheelPivot->AddLocalRotation(FRotator(0,0, WheelRotationSpeed * DeltaTime));
}

void ABoss::Attack()
{
	if (GetWorldTimerManager().IsTimerActive(ProjectileAttackTimerHandle))
		return;

	FVector location = Muzzle->GetComponentLocation();
	FRotator rotation = Muzzle->GetComponentRotation();
	
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, location, rotation);
	projectile->SetOwner(this);
	GetWorldTimerManager().SetTimer(ProjectileAttackTimerHandle, ProjectileCoolDown, false);
}

void ABoss::RandomRotationSpeed()
{
	WheelRotationSpeed = FMath::RandRange(RotationSpeedRange.X, RotationSpeedRange.Y);
	float NextRandomWaitTime = FMath::RandRange(RotationRandomIntervalRange.X, RotationRandomIntervalRange.Y);
	GetWorldTimerManager().ClearTimer(RotationIntervalHandle);
	GetWorldTimerManager().SetTimer(RotationIntervalHandle, this, &ABoss::RandomRotationSpeed, NextRandomWaitTime, false);
}

void ABoss::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AEAIControllerBase* AIC = Cast<AEAIControllerBase>(NewController);
	if (AIC)
	{
		AIC->OnTargetUpdated.AddDynamic(this, &ABoss::TargetUpdated);
	}
}

void ABoss::TargetUpdated(AActor* Target)
{
	BP_TargetUpdated(Target);
}

