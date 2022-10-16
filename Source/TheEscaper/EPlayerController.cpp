// Fill out your copyright notice in the Description page of Project Settings.


#include "EPlayerController.h"
#include "PlayerCharacter.h"
#include "HealthComponent.h"
#include "InGameUI.h"

#include "Components/InputComponent.h"

AEPlayerController::AEPlayerController()
{
	bAutoManageActiveCameraTarget = false;
	bBlockInput = false;
}

void AEPlayerController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);
	playerCharacter = Cast<APlayerCharacter>(newPawn);
	if (playerCharacter)
	{
		SetViewTarget(playerCharacter);
		playerCharacter->GetHealthComp()->OnHealthEmpty.AddDynamic(this, &AEPlayerController::PawnDead);
		SetInputMode(FInputModeGameOnly());
		SetShowMouseCursor(false);	

		if (InGameUIClass)
		{
			inGameUI = CreateWidget<UInGameUI>(this, InGameUIClass);
			inGameUI->AddToViewport();
			playerCharacter->GetHealthComp()->OnHealthChanged.AddDynamic(inGameUI, &UInGameUI::UpdateHealth);
			playerCharacter->OnWeaponGiven.AddDynamic(inGameUI, &UInGameUI::NewWeaponAquired);
			playerCharacter->OnWeaponSwitched.AddDynamic(inGameUI, &UInGameUI::WeaponSwitchedTo);
			playerCharacter->OnDestroyed.AddDynamic(this, &AEPlayerController::PawnDeathFinished);
		}
	}
	else
	{
		SetViewTargetWithBlend(newPawn, 1.f);
	}
}

void AEPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	ensure(InputComponent);
	InputComponent->BindAction("Pause", IE_Pressed, this, &AEPlayerController::TogglePause);
}

void AEPlayerController::PawnDead()
{
	playerCharacter->SetActorHiddenInGame(true);
	SetInputMode(FInputModeUIOnly());
	APawn* DeathPawn = GetWorld()->SpawnActor<APawn>(DeathPawnClass, playerCharacter->GetTransform());
	Possess(DeathPawn);
}

void AEPlayerController::PawnDeathFinished(AActor* DestroiedPawn)
{
	inGameUI->ShowGameOverScreen();
}

void AEPlayerController::CaughtFinished()
{
	inGameUI->ShowGameOverScreen();
}

void AEPlayerController::TogglePause()
{
	inGameUI->TooglePause();
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

