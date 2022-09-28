// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "ValueGauge.h"
void UInGameUI::UpdateHealth(float health, float delta, float maxHealth)
{
	healthBar->SetValue(health, delta, maxHealth);
}
