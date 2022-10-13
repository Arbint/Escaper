// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "WeaponPickup.generated.h"

/**
 * when enemy is dead, spawn a random weapon pickup
 * when pick up a weapon that the player already have, give the weapon more ammo
 * create a health regenerate pickup
 */
UCLASS()
class THEESCAPER_API AWeaponPickup : public ATriggerable
{
	GENERATED_BODY()

public:
	AWeaponPickup();

	void SetRandomWeapon();

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AWeapon> WeaponClass;

	virtual void BeginPlay() override;

private:
	virtual void OnTriggered(AActor* actor) override;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class UStaticMeshComponent* MeshComp;


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<AWeapon>> weaponClasses;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
