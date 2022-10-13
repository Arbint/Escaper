// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.h"
#include "WeaponDataManager.generated.h"

USTRUCT(BlueprintType)
struct FWeaponAnimDescription
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> Weapon;
	
	UPROPERTY(EditAnywhere)
	TMap<USkeletalMesh*, UAnimSequence*> IdleAnimMap;

	UPROPERTY(EditAnywhere)
	TMap<USkeletalMesh*, UAnimSequence*> WalkAnimMap;

	UPROPERTY(EditAnywhere)
	TMap<USkeletalMesh*, UAnimMontage*> AttackMontageMap;

	UPROPERTY(EditAnywhere)
	TMap<USkeletalMesh*, UAnimMontage*> ReloadMontageMap;

	FWeaponAnimDescription() {};
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEESCAPER_API UWeaponDataManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponDataManager();
	bool GetAnimations(const TSubclassOf<class AWeapon>& weapon, const USkeletalMesh* mesh, UAnimSequence*& IdleAnim, UAnimSequence*& WalkAnim, UAnimMontage*& AttackMontage, UAnimMontage*& ReloadMontage);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponAnimDescription> Descriptions;
};
