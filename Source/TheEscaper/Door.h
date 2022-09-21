// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API ADoor : public ATriggerable
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void SetDoorOpen(bool bIsOpen);

private:
	virtual void OnTriggered(AActor* actor) override;
	virtual void OnActorLeftTrigger(AActor* actor) override;

	int ActorsInTrigger = 0;
};
