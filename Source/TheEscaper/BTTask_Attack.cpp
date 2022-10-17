// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIBehaviorInterface.h"
#include "AIController.h"
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	IAIBehaviorInterface* AIInterface = AIC->GetPawn<IAIBehaviorInterface>();
	if (AIInterface)
	{
		AIInterface->Attack();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
