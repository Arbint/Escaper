// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSpawner.h"
#include "Components/SceneComponent.h"
#include "Triggerable.h"
// Sets default values
APickupSpawner::APickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);

	SpawnLoc = CreateDefaultSubobject<USceneComponent>("SpawnLoc");
	SpawnLoc->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnPickup();
}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupSpawner::OnPickupDestroied(AActor* Pickup)
{
	GetWorldTimerManager().ClearTimer(SpawnTimmerHandle);
	GetWorldTimerManager().SetTimer(SpawnTimmerHandle, this, &APickupSpawner::SpawnPickup, spawnInterval,false);
}

void APickupSpawner::SpawnPickup()
{
	if (PickupClasses.Num() == 0)
		return;

	int pickIndex = FMath::RandRange(0, PickupClasses.Num() - 1);
	AActor* Pickup = GetWorld()->SpawnActor(PickupClasses[pickIndex], &SpawnLoc->GetComponentTransform());
	Pickup->OnDestroyed.AddDynamic(this, &APickupSpawner::OnPickupDestroied);
}

