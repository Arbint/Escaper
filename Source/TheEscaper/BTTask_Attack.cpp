// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "ECharacterBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AECharacterBase* pawn = OwnerComp.GetAIOwner()->GetPawn<AECharacterBase>();
	if (pawn != nullptr)
	{
		pawn->Attack();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
