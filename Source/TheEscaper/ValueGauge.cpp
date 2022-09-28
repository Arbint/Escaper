// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueGauge.h"
#include "Components/Image.h"

void UValueGauge::SetValue(float newVal, float delta, float maxVal)
{
	valueImage->GetDynamicMaterial()->SetScalarParameterValue(ValueParamName, newVal/maxVal);
}
