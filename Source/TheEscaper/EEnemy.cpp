// Fill out your copyright notice in the Description page of Project Settings.


#include "EEnemy.h"
#include "Components/WidgetComponent.h"
#include "ValueGauge.h"
#include "PatrollingComponent.h"
#include "Weapon.h"
#include "WeaponPickup.h"
AEEnemy::AEEnemy()
{
	HealthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>("HealthBarComp");
	HealthBarWidgetComp->SetupAttachment(GetRootComponent());
	patrollingComp = CreateDefaultSubobject<UPatrollingComponent>("PatrollingComp");
}

void AEEnemy::BeginPlay()
{
	Super::BeginPlay();
	valueGauge = Cast<UValueGauge>(HealthBarWidgetComp->GetUserWidgetObject());

	if (RandomWeapons.Num() != 0)
	{
		int randomWeaponPick = FMath::RandRange(0, RandomWeapons.Num()-1);
		GiveWeapon(RandomWeapons[randomWeaponPick]);
	}
}

void AEEnemy::OnHealthChange(float val, float delta, float maxVal)
{
	if (valueGauge)
	{
		valueGauge->SetValue(val, delta, maxVal);
	}
}

void AEEnemy::OnDead()
{
	if (weaponPickupClass && RandomWeapons.Num() != 0)
	{
		FActorSpawnParameters spawnParam;
		spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AWeaponPickup* pickUp = GetWorld()->SpawnActor<AWeaponPickup>(weaponPickupClass, GetActorLocation(), GetActorRotation(), spawnParam);

		int randomWeaponPick = FMath::RandRange(0, RandomWeapons.Num() - 1);
		pickUp->SetPickupClass(RandomWeapons[randomWeaponPick]);
	}
}

