// Fill out your copyright notice in the Description page of Project Settings.


#include "EAIControllerBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "BehaviorTree/BlackboardComponent.h"

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
}

void AEAIControllerBase::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		GetBlackboardComponent()->SetValueAsObject(TargetBlackboardKeyName,Actor);
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TargetBlackboardKeyName);
		//do not clear the value if there is still another sense sensing the target
		//if ai lose track of you, ai goes to the last place it sees you first, wait for 2 seconds, and then if still not seeing you, go back to patrolling.
	}
}
