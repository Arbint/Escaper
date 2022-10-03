// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponEntry.h"
#include "Weapon.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWeaponEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	AWeapon* weapon = GetListItem<AWeapon>();
	if (weapon)
	{
		UTexture2D* weaponTexture = weapon->GetWeaponIcon();
		if (weaponTexture)
		{
			WeaponIcon->SetBrushFromTexture(weaponTexture);
		}

		//ammo part
		int clipAmmo, AmmoInInventory;
		if (weapon->GetAmmoStatus(clipAmmo, AmmoInInventory))
		{
			UpdateAmmo(clipAmmo, AmmoInInventory);
			weapon->OnAmmoUpdated.AddDynamic(this, &UWeaponEntry::UpdateAmmo);
		}
		else
		{
			AmmoText->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	DefaultDesiredSize = GetDesiredSize();
}

void UWeaponEntry::UpdateAmmo(int clipAmmo, int inventoryAmmo)
{
	FString TextStr = FString::FromInt(clipAmmo) + "/" + FString::FromInt(inventoryAmmo);
	AmmoText->SetText(FText::FromString(TextStr));
}
