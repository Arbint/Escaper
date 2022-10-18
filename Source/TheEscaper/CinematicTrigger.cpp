// Fill out your copyright notice in the Description page of Project Settings.


#include "CinematicTrigger.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "EPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/HUD.h"
void ACinematicTrigger::OnTriggered(AActor* actor)
{
	if (!SequenceToPlay) return;

	FMovieSceneSequencePlaybackSettings playSettings;
	playSettings.bHidePlayer = true;
	playSettings.bDisableMovementInput = true;
	playSettings.bDisableLookAtInput = true;
	playSettings.bHideHud = true;
	APlayerController* pc = UGameplayStatics::GetPlayerController(this, 0);
	AEPlayerController* epc = Cast<AEPlayerController>(pc);
	ACharacter* playerCharacter = epc->GetCharacter();
	if (epc && playerCharacter)
	{
		playerCharacter->DisableInput(pc);
		epc->SetHideUI(true);
	}
	
	ALevelSequenceActor* LevelSequenceActor;
	ULevelSequencePlayer::CreateLevelSequencePlayer(this, SequenceToPlay, playSettings, LevelSequenceActor);
	
	if (LevelSequenceActor)
	{
		LevelSequenceActor->SequencePlayer->Play();
	}

	LevelSequenceActor->SequencePlayer->OnStop.AddDynamic(this, &ACinematicTrigger::Finished);
}

void ACinematicTrigger::Finished()
{
	UE_LOG(LogTemp, Warning, TEXT("Cinematic Ended"))
	APlayerController* pc = UGameplayStatics::GetPlayerController(this, 0);
	AEPlayerController* epc = Cast<AEPlayerController>(pc);
	if (epc)
	{
		UGameplayStatics::GetPlayerCharacter(this, 0)->EnableInput(pc);
		epc->SetHideUI(false);
	}
}
