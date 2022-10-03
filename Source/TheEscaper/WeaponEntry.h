// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "WeaponEntry.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UWeaponEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "WeaponEntry")
	float SelectedSizeScale = 1.5f;

	UPROPERTY(meta = (bindWidget))
	class UImage* WeaponIcon;

	UPROPERTY(meta = (bindWidget))
	class UTextBlock* AmmoText;
		
	//called when it is added as a new entry to the parent list
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION()
	void UpdateAmmo(int clipAmmo, int inventoryAmmo);

	FVector2D DefaultDesiredSize;
};
