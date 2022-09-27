// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Weapon.h"
#include "Components/Image.h"
void UInGameUI::WeaponEquiped(AWeapon* weapon)
{
	CrossHair->SetBrushFromTexture(weapon->GetAimTexture(),true);
}