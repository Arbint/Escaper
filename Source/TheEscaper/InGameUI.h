// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void UpdateHealth(float health, float delta, float maxHealth);

	UFUNCTION()
	void NewWeaponGiven(class AWeapon* weapon);

	UFUNCTION()
	void WeaponSwitched(class AWeapon* weapon);

private:
	UPROPERTY(meta = (BindWidget))
	class UValueGauge* healthBar;

	UPROPERTY(meta = (BindWidget))
	class UImage* crossHair;

	UPROPERTY(meta = (BindWidget))
	class UListView* weaponList;
};
