// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossSpawnEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Boss.h"
#include "AIController.h"
EBTNodeResult::Type UBTTask_BossSpawnEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABoss* Boss = OwnerComp.GetAIOwner()->GetPawn<ABoss>();
	if (Boss)
	{
		Boss->SpawnEnemy();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
