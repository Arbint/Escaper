// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

void AMeleeWeapon::AttackPointAnimNotify()
{
	Super::AttackPointAnimNotify();
	FHitResult result;
	FVector ownerViewLocation;
	FRotator ownerViewRot;
	FCollisionShape capsule = FCollisionShape::MakeCapsule(40, 80);

	GetOwner()->GetActorEyesViewPoint(ownerViewLocation, ownerViewRot);

	if (GetWorld()->SweepSingleByChannel(result, ownerViewLocation, ownerViewLocation + ownerViewRot.Vector() * meleeRange, FQuat::Identity, ECC_Camera, capsule))
	{
		UGameplayStatics::ApplyDamage(result.GetActor(), GetWeaponDamage(), nullptr, GetOwner(), nullptr);
	}
}
