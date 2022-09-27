// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Weapon.h"
#include "Components/Image.h"
#include "ValueGauge.h"
void UInGameUI::WeaponEquiped(AWeapon* weapon)
{
	CrossHair->SetBrushFromTexture(weapon->GetAimTexture(),true);
}

void UInGameUI::HealthUpdated(float newValue, float delta, float maxHealth)
{
	HealthBar->UpdateValue(newValue, delta, maxHealth);
}
