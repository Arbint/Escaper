// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()
private:
	virtual void AttackPointAnimNotify() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponHitSocket;



	UPROPERTY(EditDefaultsOnly, Category = "Melee")
		float meleeRange = 60;
};
