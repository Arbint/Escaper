// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "TriggerListener.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API ATriggerListener : public ATriggerable
{
	GENERATED_BODY()
private:
	virtual void OnTriggered(AActor* actor) override;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	TScriptInterface<class ITriggerableInterface> Triggerable;
};
