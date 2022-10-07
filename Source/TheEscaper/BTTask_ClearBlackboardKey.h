// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ClearBlackboardKey.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UBTTask_ClearBlackboardKey : public UBTTaskNode
{
	GENERATED_BODY()

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere, Category = "Blackboard")
		FBlackboardKeySelector KeyToClear;

	void InitializeFromAsset(UBehaviorTree& Asset) override;
};
