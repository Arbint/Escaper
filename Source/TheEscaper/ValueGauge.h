// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ValueGauge.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UValueGauge : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "value")
	virtual void UpdateValue(float newVal, float delta, float maxVal);

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* HealthBarImage;

	UPROPERTY(EditDefaultsOnly, Category = "value")
	FName ValuePropertyName;
};
