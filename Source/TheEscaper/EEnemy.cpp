// Fill out your copyright notice in the Description page of Project Settings.


#include "EEnemy.h"
#include "Components/WidgetComponent.h"
#include "ValueGauge.h"

AEEnemy::AEEnemy()
{
	HealthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>("HealthBarComp");
	HealthBarWidgetComp->SetupAttachment(GetRootComponent());
	
}

void AEEnemy::BeginPlay()
{
	Super::BeginPlay();
	valueGauge = Cast<UValueGauge>(HealthBarWidgetComp->GetUserWidgetObject());
}

void AEEnemy::OnHealthChange(float val, float delta, float maxVal)
{
	if (valueGauge)
	{
		valueGauge->SetValue(val, delta, maxVal);
	}
}
