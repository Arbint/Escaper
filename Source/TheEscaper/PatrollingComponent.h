// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TargetPoint.h"
#include "PatrollingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEESCAPER_API UPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ATargetPoint* GetNextPatrolPoint();

private:
	UPROPERTY(EditAnywhere, Category = "Patrolling")
	TArray<ATargetPoint*> PatrolPoints;

	int currentPatrolIndex = -1;
};
