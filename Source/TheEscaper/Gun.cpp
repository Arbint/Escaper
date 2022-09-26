// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "kismet/GameplayStatics.h"

void AGun::AttackPointAnimNotify()
{
	Super::AttackPointAnimNotify();
	FHitResult result;
	FVector ownerViewLoc;
	FRotator ownerViewRot;
	GetOwner()->GetActorEyesViewPoint(ownerViewLoc, ownerViewRot);
	FVector Start = WeaponMesh->GetSocketLocation(MuzzleSocketName);
	if (GetWorld()->LineTraceSingleByChannel(result, Start, Start + ownerViewRot.Vector() * shootRange, ECC_Camera))
	{
		UE_LOG(LogTemp, Warning, TEXT("Damaging: %s"), *result.GetActor()->GetName());
		UGameplayStatics::ApplyDamage(result.GetActor(), damage, nullptr, GetOwner(), nullptr);
	}
}