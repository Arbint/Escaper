// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardKey.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
EBTNodeResult::Type UBTTask_ClearBlackboardKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->ClearValue(KeyToClear.SelectedKeyName);
	return EBTNodeResult::Succeeded;
}

void UBTTask_ClearBlackboardKey::InitializeFromAsset(UBehaviorTree& Asset)
{
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (BBAsset)
	{
		KeyToClear.ResolveSelectedKey(*BBAsset);
	}
}
