// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "kismet/GameplayStatics.h"

bool AGun::IsReloading() const
{
	return GetOwnerSkeletalMesh()->GetAnimInstance()->Montage_IsPlaying(ReloadMontage);
}

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
		K2_OnHit(result);
	}

	--ammoInClip;
	OnAmmoUpdated.Broadcast(ammoInClip, ammoInInventory);
	if (ammoInClip == 0 && ammoInInventory > 0)
	{
		Reload();
	}
}

bool AGun::GetAmmoStatus(int& OutAmmoInClip, int& OutAmmoInInventory) const
{
	OutAmmoInClip = ammoInClip; 
	OutAmmoInInventory = ammoInInventory;
	return true;
}

void AGun::Reload()
{
	if (IsReloading() || ammoInInventory <= 0) return;
	float reloadDuration = GetOwnerSkeletalMesh()->GetAnimInstance()->Montage_Play(ReloadMontage);
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AGun::ReloadTimePoint, reloadDuration, false);
}

bool AGun::CanAttack() const
{
	if (ammoInClip > 0 && !IsReloading())
	{
		return Super::CanAttack();
	}
	return false;	
}

void AGun::ReloadTimePoint()
{
	int ammonNeeded = clipCapacity - ammoInClip;
	if (ammoInInventory < ammonNeeded)
	{
		ammonNeeded = ammoInInventory;
	}

	ammoInInventory -= ammonNeeded;
	ammoInClip += ammonNeeded;
	OnAmmoUpdated.Broadcast(ammoInClip, ammoInInventory);
}

void AGun::OnPutInHand()
{
	if (ammoInClip == 0 && ammoInInventory > 0)
	{
		Reload();
	}
}

void AGun::OnBackToInventory()
{
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
}
