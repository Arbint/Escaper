// Fill out your copyright notice in the Description page of Project Settings.


#include "EAIControllerBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

AEAIControllerBase::AEAIControllerBase()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>("DamageConfig");

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->ConfigureSense(*DamageConfig);

	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEAIControllerBase::OnPerceptionUpdated);
}

void AEAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	GetBlackboardComponent()->SetValueAsObject(PlayerBlackboardKeyName, UGameplayStatics::GetPlayerController(this, 0)->GetPawn());
}

void AEAIControllerBase::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		GetBlackboardComponent()->SetValueAsObject(TargetBlackboardKeyName,Actor);
		OnTargetUpdated.Broadcast(Actor);
	}
	else
	{
		const FActorPerceptionInfo* perceptionInfo = PerceptionComp->GetActorInfo(*Actor);
		if (!perceptionInfo->HasAnyCurrentStimulus())
		{
			GetBlackboardComponent()->ClearValue(TargetBlackboardKeyName);
			GetBlackboardComponent()->SetValueAsVector(LastSeenLocKeyName, Actor->GetActorLocation());
			OnTargetUpdated.Broadcast(nullptr);
		}
	}
}

FGenericTeamId AEAIControllerBase::GetGenericTeamId() const
{
	IGenericTeamAgentInterface* PawnAsTeamInterface = GetPawn<IGenericTeamAgentInterface>();
	if (PawnAsTeamInterface)
	{
		return PawnAsTeamInterface->GetGenericTeamId();
	}
	return FGenericTeamId::NoTeam;
}
