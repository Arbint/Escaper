// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EAIControllerBase.h"
#include "Projectile.h"
#include "HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "ValueGauge.h"
#include "EEnemy.h"
#include "AIController.h"
#include "BrainComponent.h"
// Sets default values
ABoss::ABoss()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RotationPivot = CreateDefaultSubobject<USceneComponent>("RotationPivot");
	RotationPivot->SetupAttachment(RootComp);
	
	EnemySpawnPoint = CreateDefaultSubobject<USceneComponent>("EnemySpawnPoint");
	EnemySpawnPoint->SetupAttachment(RotationPivot);

	Muzzle = CreateDefaultSubobject<USceneComponent>("Muzzle");
	Muzzle->SetupAttachment(RotationPivot);

	WheelPivot = CreateDefaultSubobject<USceneComponent>("WheelPivot");
	WheelPivot->SetupAttachment(RotationPivot);

	HealthComp = CreateDefaultSubobject<UHealthComponent>("HealthComp");
	HealthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidgetComponent");
	HealthBarWidgetComp->SetupAttachment(RootComp);

	HealthComp->OnHealthChanged.AddDynamic(this, &ABoss::HealthUpdated);
	HealthComp->OnHealthEmpty.AddDynamic(this, &ABoss::Die);
}

void ABoss::SpawnEnemy()
{
	if (Target && EnemeyClass)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<AEEnemy>(EnemeyClass, EnemySpawnPoint->GetComponentTransform(), spawnParams);
	}
}

bool ABoss::LookAt(AActor* lookTarget, float DeltaTime)
{
	FRotator currentRot = RotationPivot->GetComponentRotation();
	FRotator lookRot = UKismetMathLibrary::FindLookAtRotation(RotationPivot->GetComponentLocation(), lookTarget->GetActorLocation());

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
	healthBarWidget = Cast<UValueGauge>(HealthBarWidgetComp->GetUserWidgetObject());
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

void ABoss::TargetUpdated(AActor* newTarget)
{
	Target = newTarget;
	BP_TargetUpdated(Target);
}

void ABoss::HealthUpdated(float newHealth, float Delta, float MaxHealth)
{
	if (healthBarWidget)
	{
		healthBarWidget->SetValue(newHealth, Delta, MaxHealth);
	}
}

void ABoss::Die()
{
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FRotator SpawnRot = RotationPivot->GetComponentRotation();
	UE_LOG(LogTemp, Warning, TEXT("Spawn rotation is: %s"), *SpawnRot.ToString())
	GetWorld()->SpawnActor<AActor>(DeadActorClass, GetActorLocation(), SpawnRot,spawnParams);

	AAIController* AIC = GetController<AAIController>();
	if (AIC)
	{
		AIC->GetBrainComponent()->StopLogic("Dead");
	}
	Destroy();
}

