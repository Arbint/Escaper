// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_UpdatePatrolPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "PatrollingComponent.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_UpdatePatrolPoint::UBTTask_UpdatePatrolPoint()
{
	NodeName = "Update Patrol Point";
}

EBTNodeResult::Type UBTTask_UpdatePatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UPatrollingComponent* patrollingComp = Cast<UPatrollingComponent>(OwnerComp.GetAIOwner()->GetPawn()->GetComponentByClass(UPatrollingComponent::StaticClass()));

	if (patrollingComp)
	{
		ATargetPoint* nextPatrolPoint = patrollingComp->GetNextPatrolPoint();
		if (nextPatrolPoint)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, nextPatrolPoint);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

