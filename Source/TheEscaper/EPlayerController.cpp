// Fill out your copyright notice in the Description page of Project Settings.


#include "EPlayerController.h"
#include "PlayerCharacter.h"
#include "InGameUI.h"
void AEPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	playerCharacter = Cast<APlayerCharacter>(InPawn);
	if (playerCharacter)
	{
		playerCharacter->OnWeaponSwitched.AddDynamic(this, &AEPlayerController::PawnWeaponSwitched);
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

void AEPlayerController::SpawnUI()
{
	if (InGameUIClass)
	{
		inGameUI = CreateWidget<UInGameUI>(this,InGameUIClass);
		inGameUI->AddToViewport();
	}
}
