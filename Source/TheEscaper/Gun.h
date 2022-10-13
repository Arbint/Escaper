// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API AGun : public AWeapon
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "weapon", meta=(DisplayName="OnBulletHit"))
	void BP_OnBulletHit(const FHitResult& hitResult);

	void UpdateAmmo();
	FORCEINLINE FName GetMuzzleSocketName() const { return MuzzleSocketName; }
private:
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	int ammoInClip = 7;
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	int clipCapacity = 7;
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	int ammoInInventory = 30;

	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	FName MuzzleSocketName;
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	float shootRange = 10000.f;

	virtual void AttackPointAnimNotify() override;

	virtual void Reload() override;
	virtual bool CanAttack() const override;
	bool IsReloading() const;
	FTimerHandle ReloadTimmerHandle;

	void ReloadTimePoint();
	virtual void PutInInventory() override;
	virtual bool GetAmmoStatus(int& clipAmmo, int& inventoryAmmo) const override;

};
