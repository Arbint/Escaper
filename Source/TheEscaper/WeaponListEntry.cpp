// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponListEntry.h"
#include "Components/Image.h"
#include "Weapon.h"
#include "Components/TextBlock.h"

void UWeaponListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	AWeapon* weapon = GetListItem<AWeapon>();
	weaponIcon->SetBrushFromTexture(weapon->GetWeaponIcon());
	int ammoInClip, ammoInInventory;
	if (weapon->GetAmmoStatus(ammoInClip, ammoInInventory))
	{
		UpdateAmmo(ammoInClip, ammoInInventory);
	}
	else
	{
		ammoText->SetVisibility(ESlateVisibility::Hidden);
	}
	weapon->OnAmmoUpdated.AddDynamic(this, &UWeaponListEntry::UpdateAmmo);
}

void UWeaponListEntry::UpdateAmmo(int ammoInClip, int ammoInInventory)
{
	ammoText->SetText(FText::FromString(FString::FromInt(ammoInClip) + "/" + FString::FromInt(ammoInInventory)));
}
