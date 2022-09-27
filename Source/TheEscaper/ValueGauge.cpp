// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueGauge.h"
#include "Components/Image.h"

void UValueGauge::UpdateValue(float newVal, float delta, float maxVal)
{
	HealthBarImage->GetDynamicMaterial()->SetScalarParameterValue(ValuePropertyName, newVal/maxVal);
}
