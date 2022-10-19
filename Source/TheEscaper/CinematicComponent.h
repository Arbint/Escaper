// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "CinematicComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCinematicStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCinematicEnded);
/**
 * 
 */
UCLASS(meta = (DisplayName = "CinematicTrigger", BlueprintSpawnableComponent))
class THEESCAPER_API UCinematicComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	UCinematicComponent();
	FOnCinematicStarted OnCinematicStarted;
	FOnCinematicEnded OnCinematicEnded;

private:
	UFUNCTION()
	void Triggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PlayCinematics();

	UPROPERTY(EditAnywhere, Category = "Cinematics")
	class ULevelSequence* SequenceToPlay;
	UPROPERTY(EditAnywhere, Category = "Cinematics")
	bool bTriggerOnce = true;

	bool bAlreadyTriggered = false;

	UFUNCTION()
	void CinematicEnded();
};
