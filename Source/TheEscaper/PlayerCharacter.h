// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ECharacterBase.h"

#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API APlayerCharacter : public AECharacterBase
{
	GENERATED_BODY()
public:
	APlayerCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	/*
	@ return - returns the time it takes for the caught animation to finished.
	*/
	float Caught();

private:
	void MoveForward(float amt);
	void MoveRight(float amt);
	void Turn(float amt);
	void LookUp(float amt);

	UPROPERTY(VisibleDefaultsOnly, Category = "player")
	class UCameraComponent* playerEye;

	UPROPERTY(EditDefaultsOnly, Category = "player")
	UAnimMontage* CaughtMontage;

	UPROPERTY(EditDefaultsOnly, Category = "player")
	FName LazerSocketName = "LazerGunSocket";

	UPROPERTY(VisibleDefaultsOnly, Category = "player")
	class ULazerGunComponent* LazerGun;

	void LazerOn();

	void LazerOff();
};
