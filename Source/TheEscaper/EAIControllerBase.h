// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EAIControllerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetUpdated, AActor*, newTarget);
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
	FOnTargetUpdated OnTargetUpdated;
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "AI")
	class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY()
	class UAISenseConfig_Damage* DamageConfig;
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName TargetBlackboardKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PlayerBlackboardKeyName;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LastSeenLocKeyName;

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;

	virtual FGenericTeamId GetGenericTeamId() const override;
};
