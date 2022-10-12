// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearBlackboardEntry.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UBTTask_ClearBlackboardEntry : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_ClearBlackboardEntry();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
