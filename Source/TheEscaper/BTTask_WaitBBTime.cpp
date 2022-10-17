// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_WaitBBTime.h"

UBTTask_WaitBBTime::UBTTask_WaitBBTime()
{
	NodeName = "WaitBB";
	WaitTime = 5.0f;
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTTask_WaitBBTime::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FBTWaitBBTaskMemory* MyMemory = CastInstanceNodeMemory<FBTWaitBBTaskMemory>(NodeMemory);
	MyMemory->RemainingWaitTime = FMath::FRandRange(FMath::Max(0.0f, WaitTime - RandomDeviation), (WaitTime + RandomDeviation));

	return EBTNodeResult::InProgress;
}

uint16 UBTTask_WaitBBTime::GetInstanceMemorySize() const
{
	return sizeof(FBTWaitBBTaskMemory);
}

void UBTTask_WaitBBTime::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	FBTWaitBBTaskMemory* MyMemory = CastInstanceNodeMemory<FBTWaitBBTaskMemory>(NodeMemory);
	if (MyMemory->RemainingWaitTime)
	{
		Values.Add(FString::Printf(TEXT("remaining: %ss"), *FString::SanitizeFloat(MyMemory->RemainingWaitTime)));
	}
}

FString UBTTask_WaitBBTime::GetStaticDescription() const
{
	if (FMath::IsNearlyZero(RandomDeviation))
	{
		return FString::Printf(TEXT("%s: %.1fs"), *Super::GetStaticDescription(), WaitTime);
	}
	else
	{
		return FString::Printf(TEXT("%s: %.1f+-%.1fs"), *Super::GetStaticDescription(), WaitTime, RandomDeviation);
	}
}

#if WITH_EDITOR

FName UBTTask_WaitBBTime::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
}

#endif	// WITH_EDITOR

void UBTTask_WaitBBTime::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FBTWaitBBTaskMemory* MyMemory = CastInstanceNodeMemory<FBTWaitBBTaskMemory>(NodeMemory);
	MyMemory->RemainingWaitTime -= DeltaSeconds;

	if (MyMemory->RemainingWaitTime <= 0.0f)
	{
		// continue execution from this node
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
