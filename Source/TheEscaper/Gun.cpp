// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"
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
		UGameplayStatics::ApplyDamage(result.GetActor(), GetWeaponDamage(), nullptr, GetOwner(), nullptr);
		UAISense_Damage::ReportDamageEvent(this, result.GetActor(), GetOwner(), GetWeaponDamage(), GetActorLocation(), result.ImpactPoint);
		BP_OnBulletHit(result);
	}

	UpdateAmmo();
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

void AGun::PutInHand()
{
	Super::PutInHand();
	if (ammoInClip <= 0 && ammoInInventory >= 0 && IsActiveWeapon())
	{
		Reload();
	}
}

bool AGun::GetAmmoStatus(int& clipAmmo, int& inventoryAmmo) const
{
	clipAmmo = ammoInClip;
	inventoryAmmo = ammoInInventory;
	return true;
}

void AGun::ReplenishAmmo(int amt)
{
	ammoInInventory += amt;
	OnAmmoUpdated.Broadcast(ammoInClip, ammoInInventory);
	if (ammoInClip <= 0 && ammoInInventory >= 0 && IsActiveWeapon())
	{
		Reload();
	}
}

void AGun::UpdateAmmo()
{
	ammoInClip--;
	OnAmmoUpdated.Broadcast(ammoInClip, ammoInInventory);
	if (ammoInClip == 0)
	{
		Reload();
	}
}

bool AGun::CanAttack() const
{
	if (IsReloading() || ammoInClip == 0) return false;

	return Super::CanAttack();
}
