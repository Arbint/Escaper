// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EPlayerController.generated.h"

class UInGameUI;
/**
 * 
 */
UCLASS()
class THEESCAPER_API AEPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AEPlayerController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void TestDead();
private:
	class APlayerCharacter* playerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UInGameUI> InGameUIClass;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
	TSubclassOf<class APawn> DeathPawnClass;

	UInGameUI* inGameUI;

	UFUNCTION()
	void PawnWeaponSwitched(class AWeapon* weapon);
	UFUNCTION()
	void HealthChanged(float newVal, float delta, float maxHealth);

	UFUNCTION()
	void PawnDead();

	void SpawnUI();
};
