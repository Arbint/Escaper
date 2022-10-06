// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ECharacterBase.h"
#include "EEnemy.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API AEEnemy : public AECharacterBase
{
	GENERATED_BODY()
public:
	AEEnemy();
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	class UWidgetComponent* HealthBarWidgetComp;

	class UValueGauge* valueGauge;
	virtual void OnHealthChange(float val, float delta, float maxVal) override;

	UPROPERTY(EditAnywhere, Category = "Patrolling")
		class UPatrollingComponent* patrollingComp;
};
