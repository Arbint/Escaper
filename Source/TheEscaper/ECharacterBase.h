// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ECharacterBase.generated.h"

class AWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponSwtiched, AWeapon*, weapon);

UCLASS()
class THEESCAPER_API AECharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AECharacterBase();
	FOnWeaponSwtiched OnWeaponSwitched;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "weapon")
	void GiveWeapon(TSubclassOf<AWeapon> weaponClass);

	UFUNCTION(BlueprintCallable, Category = "weapon")
	FORCEINLINE	AWeapon* GetCurrentWeapon() const { return currentWeapon; }

	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComp; }

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Attack();

	void PrevWeapon();

	void NextWeapon();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* WeaponSwitchMontage;
	FTimerHandle WeaponSwitchingHandle;
	void WeaponSwitchTimePoint();

	UPROPERTY()
	TArray<AWeapon*> weapons;

	AWeapon* currentWeapon;

	int weaponIndex = -1;

	bool HasWeaponOfType(TSubclassOf<AWeapon> weaponClass) const;

	void EquipWeapon(int index);

	UPROPERTY(VisibleAnywhere, Category = "Health")
	class UHealthComponent* HealthComp;
};
