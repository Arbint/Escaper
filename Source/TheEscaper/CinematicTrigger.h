// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "CinematicTrigger.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API ACinematicTrigger : public ATriggerable
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Sequence")
	class ULevelSequence* SequenceToPlay;


	virtual void OnTriggered(AActor* actor) override;

	UFUNCTION()
	void Finished();
};
