// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Launcher.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API ALauncher : public AGun
{
	GENERATED_BODY()
public:
	ALauncher();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UStaticMeshComponent* grenadeMesh;

private:
	virtual void AttackPointAnimNotify() override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<class AProjectile> projectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		float projectileInitialSpeed = 2000;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		float projectileMaxSpeed = 2000;
};
