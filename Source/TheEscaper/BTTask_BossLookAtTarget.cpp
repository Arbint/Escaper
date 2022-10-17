// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossLookAtTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Boss.h"
#include "AIController.h"
UBTTask_BossLookAtTarget::UBTTask_BossLookAtTarget()
{
	NodeName = "Boss Look at target";
	INIT_TASK_NODE_NOTIFY_FLAGS();
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_BossLookAtTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FBTLookTargetMemory* memo = CastInstanceNodeMemory<FBTLookTargetMemory>(NodeMemory);
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	memo->Boss = Cast<ABoss>(OwnerComp.GetAIOwner()->GetPawn());
	return EBTNodeResult::InProgress;
}

void UBTTask_BossLookAtTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	FBTLookTargetMemory* memo = CastInstanceNodeMemory<FBTLookTargetMemory>(NodeMemory);
	if (Target && memo->Boss)
	{
		if (memo->Boss->LookAt(Target, DeltaSeconds))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

uint16 UBTTask_BossLookAtTarget::GetInstanceMemorySize() const
{
	return sizeof(FBTLookTargetMemory);
}
