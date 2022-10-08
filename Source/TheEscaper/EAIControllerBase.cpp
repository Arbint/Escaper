// Fill out your copyright notice in the Description page of Project Settings.


#include "EAIControllerBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Damage.h"


AEAIControllerBase::AEAIControllerBase()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");

	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>("DamageConfig");

	if (SightConfig && PerceptionComp && DamageConfig)
	{
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->SightRadius = 5200.f;
		SightConfig->LoseSightRadius = 5200.f;
		SightConfig->PeripheralVisionAngleDegrees = 45.f;
		PerceptionComp->ConfigureSense(*SightConfig);
		
		DamageConfig->SetMaxAge(DamageMaxAge);
		PerceptionComp->ConfigureSense(*DamageConfig);
		PerceptionComp->SetDominantSense(UAISense_Sight::StaticClass());
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
		if (UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus) == UAISense_Sight::StaticClass())
		{
			//UE_LOG(LogTemp, Warning, TEXT("seeing target: %s"), *Actor->GetName())
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("hurt by target: %s"), *Actor->GetName())
		}

		GetBlackboardComponent()->SetValueAsObject(TargetBBName, Actor);
	}
	else
	{
		const FActorPerceptionInfo* info = PerceptionComp->GetActorInfo(*Actor);
		if (!info->HasAnyCurrentStimulus())
		{
			//UE_LOG(LogTemp, Warning, TEXT("Losing perception"))
			GetBlackboardComponent()->ClearValue(TargetBBName);
			GetBlackboardComponent()->SetValueAsVector(LastSeenBBName, Actor->GetActorLocation());
		}
		
	}
}
