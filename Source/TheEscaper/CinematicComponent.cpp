// Fill out your copyright notice in the Description page of Project Settings.


#include "CinematicComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequence/public/LevelSequencePlayer.h"
#include "LevelSequence/public/LevelSequence.h"
#include "LevelSequence/public/LevelSequenceActor.h"
UCinematicComponent::UCinematicComponent()
{
	OnComponentBeginOverlap.AddDynamic(this, &UCinematicComponent::Triggered);
}

void UCinematicComponent::Triggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
	{
		PlayCinematics();
	}
}

void UCinematicComponent::PlayCinematics()
{
	if (bTriggerOnce && bAlreadyTriggered)
		return;
	
	bAlreadyTriggered = true;

	if (SequenceToPlay)
	{
		FMovieSceneSequencePlaybackSettings playSettings;
		playSettings.bHideHud = true;
		playSettings.bHidePlayer = true;
		playSettings.bDisableMovementInput = true;
		playSettings.bRestoreState = false;
		ALevelSequenceActor* SequenceActor;
		ULevelSequencePlayer::CreateLevelSequencePlayer(this, SequenceToPlay, playSettings, SequenceActor);
		SequenceActor->SequencePlayer->Play();
		OnCinematicStarted.Broadcast();
		SequenceActor->SequencePlayer->OnStop.AddDynamic(this, &UCinematicComponent::CinematicEnded);
	}
}

void UCinematicComponent::CinematicEnded()
{
	OnCinematicEnded.Broadcast();
}
