// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API AHealthPickup : public ATriggerable
{
	GENERATED_BODY()
public:
	AHealthPickup();

private:


	virtual void OnTriggered(AActor* actor) override;
	virtual void OnActorLeftTrigger(AActor* actor) override;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float healAmount = 30;
};
