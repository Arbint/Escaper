// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardEntry.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
UBTTask_ClearBlackboardEntry::UBTTask_ClearBlackboardEntry()
{
	NodeName = "Clear Blackboard Entry";
}

EBTNodeResult::Type UBTTask_ClearBlackboardEntry::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
	return EBTNodeResult::Succeeded;
}
