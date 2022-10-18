// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API AEPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEPlayerController();
	virtual void OnPossess(APawn* newPawn) override;
	virtual void SetupInputComponent() override;

	void Caught();

	void SetHideUI(bool bHide);

private:
	class APlayerCharacter* playerCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Player")
		TSubclassOf<APawn> DeathPawnClass;
	UPROPERTY(EditDefaultsOnly, Category = "Player")
		TSubclassOf<class UInGameUI> InGameUIClass;

	UFUNCTION()
	void PawnDead();

	UFUNCTION()
	void PawnDeathFinished(AActor* DestroiedPawn);

	UInGameUI* inGameUI;
	FTimerHandle CaughtTimerHandle;
	void CaughtFinished();
	bool bIsCaught;

	void TogglePause();
};
