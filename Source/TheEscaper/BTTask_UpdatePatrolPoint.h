// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_UpdatePatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UBTTask_UpdatePatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_UpdatePatrolPoint();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
