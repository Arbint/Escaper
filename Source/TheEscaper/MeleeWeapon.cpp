// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

void AMeleeWeapon::AttackPointAnimNotify()
{
	Super::AttackPointAnimNotify();
	FVector ownerViewLocation;
	FRotator ownerViewRot;
	FCollisionShape capsule = FCollisionShape::MakeCapsule(40, 80);

	GetOwner()->GetActorEyesViewPoint(ownerViewLocation, ownerViewRot);
	TArray<FHitResult> results;
	if (GetWorld()->SweepMultiByChannel(results, ownerViewLocation, ownerViewLocation + ownerViewRot.Vector() * meleeRange, FQuat::Identity, ECC_Camera, capsule))
	{
		for (const FHitResult& result : results)
		{
			if (result.GetActor() != GetOwner())
			{
				UGameplayStatics::ApplyDamage(result.GetActor(), GetWeaponDamage(), nullptr, GetOwner(), nullptr);
			}
		}
	}
}
