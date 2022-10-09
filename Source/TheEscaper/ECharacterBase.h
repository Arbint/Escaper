// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ECharacterBase.generated.h"


class AWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponGiven, AWeapon*, weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponSwitched, AWeapon*, weapon);

UCLASS()
class THEESCAPER_API AECharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AECharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	FOnWeaponGiven OnWeaponGiven;
	FOnWeaponSwitched OnWeaponSwitched;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "weapon")
	void GiveWeapon(TSubclassOf<AWeapon> weaponClass);

	UFUNCTION(BlueprintCallable, Category = "weapon")
	FORCEINLINE	AWeapon* GetCurrentWeapon() const { return currentWeapon; }
	FORCEINLINE class UHealthComponent* GetHealthComp() const { return healthComp; }

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Attack();
protected:

	void PrevWeapon();

	void NextWeapon();
	
	UFUNCTION()
	void Reload();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* WeaponSwitchMontage;
	FTimerHandle WeaponSwitchingHandle;
	void WeaponSwitchTimePoint();
	
	UPROPERTY()
	TArray<AWeapon*> weapons;

	AWeapon* currentWeapon;

	int weaponIndex = -1;
	/*
		@ return - returns the weapon found of the type weaponClass, null if don't have weapon of type
	*/
	AWeapon* HasWeaponOfType(TSubclassOf<AWeapon> weaponClass) const;

	void EquipWeapon(int index);

	UPROPERTY(VisibleDefaultsOnly, Category = "Health")
	class UHealthComponent* healthComp;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	UFUNCTION()
	void HealthChanged(float val, float delta, float maxVal);
	UFUNCTION()
	void StartDeathSequence();

	virtual void OnHealthChange(float val, float delta, float maxVal);
	virtual void OnDeathStarted();

	void Dead();
	virtual void OnDead();
	FTimerHandle DeathTimerHandle;
	bool bIsDead;

	void DisableGameplayRelavency();
};
