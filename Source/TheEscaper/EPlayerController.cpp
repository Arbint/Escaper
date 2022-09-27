// Fill out your copyright notice in the Description page of Project Settings.


#include "EPlayerController.h"
#include "PlayerCharacter.h"
#include "InGameUI.h"
#include "HealthComponent.h"
void AEPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	playerCharacter = Cast<APlayerCharacter>(InPawn);
	if (playerCharacter)
	{
		playerCharacter->OnWeaponSwitched.AddDynamic(this, &AEPlayerController::PawnWeaponSwitched);
		playerCharacter->GetHealthComponent()->OnHealthChanged.AddDynamic(this, &AEPlayerController::HealthChanged);
	}
}

void AEPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SpawnUI();
}

void AEPlayerController::PawnWeaponSwitched(AWeapon* weapon)
{
	if (inGameUI)
	{
		inGameUI->WeaponEquiped(weapon);
	}
}

void AEPlayerController::HealthChanged(float newVal, float delta, float maxHealth)
{
	if (inGameUI)
	{
		inGameUI->HealthUpdated(newVal, delta, maxHealth);
	}
}

void AEPlayerController::SpawnUI()
{
	if (InGameUIClass)
	{
		inGameUI = CreateWidget<UInGameUI>(this,InGameUIClass);
		inGameUI->AddToViewport();
	}
}
