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
public:

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "vfx", meta = (DisplayName = "OnHit"))
	void K2_OnHit(const FHitResult& hitResult);

private:
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
		int ammoInInventory = 30;
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
		int clipCapacity = 7;
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
		int ammoInClip = 7;

	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	UAnimMontage* ReloadMontage;
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	FName MuzzleSocketName;
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	float shootRange = 10000.f;
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	float damage = 10.f;
	virtual void AttackPointAnimNotify() override;


	virtual bool GetAmmoStatus(int& OutAmmoInClip, int& OutAmmoInInventory) const override;
	bool IsReloading() const;
	virtual void Reload() override;
	virtual bool CanAttack() const override;
	void ReloadTimePoint();
	FTimerHandle ReloadTimerHandle;

	virtual void OnPutInHand() override;
	virtual void OnBackToInventory() override;
};
