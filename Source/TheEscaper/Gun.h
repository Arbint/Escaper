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
private:
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	FName MuzzleSocketName;
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	float shootRange = 10000.f;
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	float damage = 10.f;
	virtual void AttackPointAnimNotify() override;
};
