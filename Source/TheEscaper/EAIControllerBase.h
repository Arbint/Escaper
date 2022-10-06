// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EAIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API AEAIControllerBase : public AAIController
{
	GENERATED_BODY()
public:
	AEAIControllerBase();
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Perception")
	class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditDefaultsOnly, Category = "Perception")
	FName TargetBBName;
	UPROPERTY(EditDefaultsOnly, Category = "Perception")
	class UBehaviorTree* BehaviorTree;
};
