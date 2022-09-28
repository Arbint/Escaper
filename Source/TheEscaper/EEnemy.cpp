// Fill out your copyright notice in the Description page of Project Settings.


#include "EEnemy.h"
#include "Components/WidgetComponent.h"
#include "HealthComponent.h"
#include "ValueGauge.h"
AEEnemy::AEEnemy()
{
	healthWidgetComp = CreateDefaultSubobject<UWidgetComponent>("healthWidgetComp");
	healthWidgetComp->SetupAttachment(GetRootComponent());
}

void AEEnemy::BeginPlay()
{
	Super::BeginPlay();
	healthBar = Cast<UValueGauge>(healthWidgetComp->GetUserWidgetObject());
}

void AEEnemy::OnHealthChanged(float newVal, float delta, float maxHealth)
{
	if (healthBar)
	{
		healthBar->UpdateValue(newVal, delta, maxHealth);
	}
}
