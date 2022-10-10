// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "ECharacterBase.h"
#include "AIController.h"
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	AECharacterBase* characterBase = AIC->GetPawn<AECharacterBase>();
	characterBase->Attack();
	return EBTNodeResult::Succeeded;
}
