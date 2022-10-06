// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_NextPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UBTTask_NextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector PatrolPointKey;
	
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

};
