// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDataManager.h"

// Sets default values for this component's properties
UWeaponDataManager::UWeaponDataManager()
{

}

bool UWeaponDataManager::GetAnimations(const TSubclassOf<class AWeapon>& weapon, const USkeletalMesh* mesh, UAnimSequence*& IdleAnim, UAnimSequence*& WalkAnim, UAnimMontage*& AttackMontage, UAnimMontage*& ReloadMontage)
{
	FWeaponAnimDescription* discription = Descriptions.FindByPredicate([weapon](const FWeaponAnimDescription& dec) { return dec.Weapon == weapon; });
	if (discription)
	{
		IdleAnim = discription->IdleAnimMap[mesh];
		WalkAnim = discription->WalkAnimMap[mesh];
		AttackMontage = discription->AttackMontageMap[mesh];
		ReloadMontage = discription->ReloadMontageMap[mesh];

		return IdleAnim && WalkAnim && AttackMontage && ReloadMontage;
	}
	return false;
}


