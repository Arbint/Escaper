// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoUpdated, int, clipAmmo, int, inventoryAmmo);

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnAquired(class USkeletalMeshComponent* OwnerMesh);

	void Attack();

	UFUNCTION(BlueprintPure, Category = "Animation")
	void GetAnims(UAnimSequence*& Idle, UAnimSequence*& Walk, UAnimMontage*& Attack) const;

	FORCEINLINE UTexture2D* GetCrossHairTexture() const { return crossHairTexture; }
	FORCEINLINE UTexture2D* GetWeaponIcon() const { return weaponIcon; }
	
	/*
	get the amount of ammo
	@ return - false if not ammo based
	*/
	virtual bool GetAmmoStatus(int& OutAmmoInClip, int& OutAmmoInInventory) const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void AttackPointAnimNotify();

	virtual void Reload();

	virtual void BackToInventory();
	
	virtual void PutInHand();

	FOnAmmoUpdated OnAmmoUpdated;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	class UStaticMeshComponent* WeaponMesh;
	virtual bool CanAttack() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FORCEINLINE USkeletalMeshComponent* GetOwnerSkeletalMesh() const { return OwnerSkeletalMesh; }

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	class USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimSequence* IdleAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimSequence* WalkAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UTexture2D* crossHairTexture;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UTexture2D* weaponIcon;

	USkeletalMeshComponent* OwnerSkeletalMesh;

	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	float firingRate = 1.f;

	FTimerHandle FiringTimmer;

	virtual void OnBackToInventory();
	virtual void OnPutInHand();
};
