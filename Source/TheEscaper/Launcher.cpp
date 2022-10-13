// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"
#include "Projectile.h"

ALauncher::ALauncher()
{
	grenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade"));
	grenadeMesh->SetupAttachment(RootComponent);
}

void ALauncher::AttackPointAnimNotify()
{
	FVector location = WeaponMesh->GetSocketLocation(GetMuzzleSocketName());
	FRotator rotation = WeaponMesh->GetSocketRotation(GetMuzzleSocketName());
	grenadeMesh->SetHiddenInGame(true);
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileClass, location, rotation);
	projectile->SetInitialSpeed(projectileInitialSpeed);
	projectile->SetMaxSpeed(projectileMaxSpeed);
	projectile->SetDamage(GetWeaponDamage());
	//this won't trigger the OnHit event..not sure why. Too fast? Simulate Physics?
	//projectile->GetMesh()->SetSimulatePhysics(true);
	//projectile->GetMesh()->AddImpulse(projectile->GetActorForwardVector() * projectileRange, NAME_None, false);
	projectile->SetOwner(this);
	UpdateAmmo();
}

