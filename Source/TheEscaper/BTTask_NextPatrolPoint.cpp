// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NextPatrolPoint.h"
#include "PatrollingComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_NextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UPatrollingComponent* patrollingComp = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrollingComponent>();
	ATargetPoint* nextPatrolPoint = patrollingComp->NextPatrolPoint();
	if (nextPatrolPoint)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(PatrolPointKey.SelectedKeyName, nextPatrolPoint);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UBTTask_NextPatrolPoint::InitializeFromAsset(UBehaviorTree& Asset)
{
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (BBAsset)
	{
		PatrolPointKey.ResolveSelectedKey(*BBAsset);
	}
}
