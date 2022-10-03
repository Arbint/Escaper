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
	if (GetWorld()->LineTraceSingleByChannel(result, Start, ownerViewLoc + ownerViewRot.Vector() * shootRange, ECC_Camera))
	{
		UGameplayStatics::ApplyDamage(result.GetActor(), damage, nullptr, GetOwner(), nullptr);
		BP_OnBulletHit(result);
	}

	ammoInClip--;
	OnAmmoUpdated.Broadcast(ammoInClip, ammoInInventory);
	if (ammoInClip == 0)
	{
		Reload();
	}
}

void AGun::Reload()
{
	if (IsReloading() || ammoInClip >= clipCapacity) return;

	float reloadDuration = GetOwnerSkeletalMesh()->GetAnimInstance()->Montage_Play(ReloadMontage);
	GetWorldTimerManager().SetTimer(ReloadTimmerHandle, this, &AGun::ReloadTimePoint, reloadDuration, false);
}

bool AGun::IsReloading() const
{
	return GetOwnerSkeletalMesh()->GetAnimInstance()->Montage_IsPlaying(ReloadMontage);
}

void AGun::ReloadTimePoint()
{
	int ammoNeeded = clipCapacity - ammoInClip;
	if (ammoNeeded > ammoInInventory)
	{
		ammoNeeded = ammoInInventory;
	}

	ammoInInventory -= ammoNeeded;
	ammoInClip += ammoNeeded;
	OnAmmoUpdated.Broadcast(ammoInClip, ammoInInventory);
}

void AGun::PutInInventory()
{
	Super::PutInInventory();
	GetWorldTimerManager().ClearTimer(ReloadTimmerHandle);
}

bool AGun::GetAmmoStatus(int& clipAmmo, int& inventoryAmmo) const
{
	clipAmmo = ammoInClip;
	inventoryAmmo = ammoInInventory;
	return true;
}

bool AGun::CanAttack() const
{
	if (IsReloading() || ammoInClip == 0) return false;

	return Super::CanAttack();
}
