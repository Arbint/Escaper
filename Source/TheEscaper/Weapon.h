// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoUpdated, int, ammoInClip, int, ammoInInventory);

UCLASS()
class THEESCAPER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	FOnAmmoUpdated OnAmmoUpdated;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnAquired(class USkeletalMeshComponent* OwnerMesh);
	virtual void ReplenishAmmo(int amt);

	virtual void Attack();
	virtual void Reload();

	virtual void PutInInventory();
	virtual void PutInHand();

	UFUNCTION(BlueprintPure, Category = "Animation")
	void GetAnims(UAnimSequence*& Idle, UAnimSequence*& Walk, UAnimMontage*& Attack) const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void AttackPointAnimNotify();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FORCEINLINE USkeletalMeshComponent* GetOwnerSkeletalMesh() const { return OwnerSkeletalMesh; }

	FORCEINLINE UTexture2D* GetCrossHairTexture() const { return crossHairTexture; }
	FORCEINLINE UTexture2D* GetWeaponIcon() const { return weaponIconTexture; }

	FORCEINLINE UStaticMesh* GetMesh() const { return WeaponMesh->GetStaticMesh(); }
	FORCEINLINE bool IsActiveWeapon() const { return bIsActiveWeapon; }

	/*
	@ return - false if not firearm
	*/
	virtual bool GetAmmoStatus(int& clipAmmo, int& inventoryAmmo) const;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TMap<USkeletalMesh*, UAnimMontage*> ReoloadMontageMap;

	UAnimMontage* ReloadMontage;

	virtual bool CanAttack() const;

	float GetWeaponDamage() const { return damage; }

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	class USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TMap<USkeletalMesh*, UAnimSequence*> IdleAnimMap;

	UAnimSequence* IdleAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TMap<USkeletalMesh*, UAnimSequence*> WalkAnimMap;

	UAnimSequence* WalkAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TMap<USkeletalMesh*, UAnimMontage*> AttackMontageMap;

	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UTexture2D* crossHairTexture;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UTexture2D* weaponIconTexture;


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocket;

	USkeletalMeshComponent* OwnerSkeletalMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	float firingRate = 1.f;
	FTimerHandle FiringTimmer;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float damage = 10.f;

	bool bIsActiveWeapon;
};
