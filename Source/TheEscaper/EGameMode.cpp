// Fill out your copyright notice in the Description page of Project Settings.


#include "EGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
void AEGameMode::RestartCurrentLevel()
{
	UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
}

void AEGameMode::QuitGame(APlayerController* pc)
{
	UKismetSystemLibrary::QuitGame(this, pc, EQuitPreference::Quit, true);
}
