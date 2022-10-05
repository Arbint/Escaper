// Fill out your copyright notice in the Description page of Project Settings.


#include "EPlayerController.h"
#include "PlayerCharacter.h"
#include "HealthComponent.h"
#include "InGameUI.h"

AEPlayerController::AEPlayerController()
{
	bAutoManageActiveCameraTarget = false;
}

void AEPlayerController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);
	playerCharacter = Cast<APlayerCharacter>(newPawn);
	if (playerCharacter)
	{
		SetViewTarget(playerCharacter);
		playerCharacter->GetHealthComp()->OnHealthEmpty.AddDynamic(this, &AEPlayerController::PawnDead);

		if (InGameUIClass)
		{
			inGameUI = CreateWidget<UInGameUI>(this, InGameUIClass);
			inGameUI->AddToViewport();
			playerCharacter->GetHealthComp()->OnHealthChanged.AddDynamic(inGameUI, &UInGameUI::UpdateHealth);
			playerCharacter->OnWeaponGiven.AddDynamic(inGameUI, &UInGameUI::NewWeaponGiven);
			playerCharacter->OnWeaponSwitched.AddDynamic(inGameUI, &UInGameUI::WeaponSwitched);
		}
	}
	else
	{
		SetViewTargetWithBlend(newPawn, 1.f);
	}
}

void AEPlayerController::PawnDead()
{
	playerCharacter->SetActorHiddenInGame(true);
	SetInputMode(FInputModeUIOnly());
	APawn* DeathPawn = GetWorld()->SpawnActor<APawn>(DeathPawnClass, playerCharacter->GetTransform());
	Possess(DeathPawn);
}

void AEPlayerController::CaughtFinished()
{
	inGameUI->SwitchToGameOverMenu();
}

void AEPlayerController::Caught()
{
	if (bIsCaught)
		return;

	bIsCaught = true;
	float caugthAnimationDuration = playerCharacter->Caught();
	SetInputMode(FInputModeUIOnly());
	GetWorldTimerManager().SetTimer(CaughtTimerHandle, this, &AEPlayerController::CaughtFinished, caugthAnimationDuration, false);
}

