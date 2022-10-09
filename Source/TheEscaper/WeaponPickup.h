// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "WeaponPickup.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API AWeaponPickup : public ATriggerable
{
	GENERATED_BODY()

public:
	AWeaponPickup();
	virtual void BeginPlay() override;
	FORCEINLINE void SetPickupClass(const TSubclassOf<class AWeapon>& newClass) { weaponClass = weaponClass; }
private:
	virtual void OnTriggered(AActor* actor) override;

	UPROPERTY()
	UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AWeapon> weaponClass;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
