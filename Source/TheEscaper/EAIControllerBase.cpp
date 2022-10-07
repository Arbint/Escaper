// Fill out your copyright notice in the Description page of Project Settings.


#include "EAIControllerBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AEAIControllerBase::AEAIControllerBase()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	if (SightConfig && PerceptionComp)
	{
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->SightRadius = 1000.f;
		SightConfig->LoseSightRadius = 1200.f;
		SightConfig->PeripheralVisionAngleDegrees = 45.f;
		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEAIControllerBase::PerceptionUpdated);
	}
}

void AEAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
}

void AEAIControllerBase::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	ACharacter* pc = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (Actor != pc) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		GetBlackboardComponent()->SetValueAsObject(TargetBBName, Actor);
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TargetBBName);
		GetBlackboardComponent()->SetValueAsVector(LastSeenBBName, Actor->GetActorLocation());
	}
}
