// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "WeaponListEntry.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UWeaponListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
private:
	/** Follows the same pattern as the NativeOn[X] methods in UUserWidget - super calls are expected in order to route the event to BP. */
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);

	UPROPERTY(meta = (bindWidget))
	class UImage* weaponIcon;

	UPROPERTY(meta = (bindWidget))
	class UTextBlock* ammoText;

	UFUNCTION()
	void UpdateAmmo(int ammoInClip, int ammoInInventory);
};
