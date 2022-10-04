// Fill out your copyright notice in the Description page of Project Settings.


#include "EGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AEGameMode::QuitGame(APlayerController* playerToQuit)
{
	UKismetSystemLibrary::QuitGame(this, playerToQuit, EQuitPreference::Quit, true);
}

void AEGameMode::RestartCurrentLevel()
{
	UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)), true);
}
