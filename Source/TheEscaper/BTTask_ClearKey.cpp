// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearKey.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearKey::UBTTask_ClearKey()
{
	NodeName = "Clear Blackboard Key";
}

EBTNodeResult::Type UBTTask_ClearKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
	return EBTNodeResult::Succeeded;
}
