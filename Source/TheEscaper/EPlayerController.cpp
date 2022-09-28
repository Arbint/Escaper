// Fill out your copyright notice in the Description page of Project Settings.


#include "EPlayerController.h"
#include "PlayerCharacter.h"
#include "InGameUI.h"
#include "HealthComponent.h"
AEPlayerController::AEPlayerController()
{
	bAutoManageActiveCameraTarget = false;
}

void AEPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	playerCharacter = Cast<APlayerCharacter>(InPawn);
	if (playerCharacter)
	{
		SetViewTargetWithBlend(InPawn);
		playerCharacter->OnWeaponSwitched.AddDynamic(this, &AEPlayerController::PawnWeaponSwitched);
		playerCharacter->GetHealthComponent()->OnHealthChanged.AddDynamic(this, &AEPlayerController::HealthChanged);
		playerCharacter->GetHealthComponent()->OnHealthEmpty.AddDynamic(this, &AEPlayerController::PawnDead);
	}
	else
	{
		SetViewTargetWithBlend(InPawn, 1.f, EViewTargetBlendFunction::VTBlend_EaseInOut, 1);
	}
}

void AEPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SpawnUI();
}

void AEPlayerController::TestDead()
{
	PawnDead();
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

void AEPlayerController::PawnDead()
{
	SetInputMode(FInputModeUIOnly());
	playerCharacter->SetActorHiddenInGame(true);
	if (DeathPawnClass)
	{
		APawn* deathPawn = GetWorld()->SpawnActor<APawn>(DeathPawnClass, playerCharacter->GetActorTransform());
		if (deathPawn)
		{
			Possess(deathPawn);
		}
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
