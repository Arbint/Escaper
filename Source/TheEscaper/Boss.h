// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIBehaviorInterface.h"
#include "Boss.generated.h"

UCLASS()
class THEESCAPER_API ABoss : public APawn, public IAIBehaviorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoss();
	bool LookAt(AActor* Target, float DeltaTime);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Boss", Meta = (DisplayName = "TargetUpdated"))
	void BP_TargetUpdated(AActor* Target);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Attack() override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	class USceneComponent* RootComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	class USceneComponent* RotationPivot;

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	class USceneComponent* Muzzle;

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	class USceneComponent* WheelPivot;

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	FVector2D RotationSpeedRange {10, -10};
	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	FVector2D RotationRandomIntervalRange {1, 3};

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	float RotationLerpSpeed = 20.f;

	float WheelRotationSpeed;
	FTimerHandle RotationIntervalHandle;
	void RandomRotationSpeed();

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	void TargetUpdated(AActor* Target);


	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	float ProjectileCoolDown = 1.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	TSubclassOf<class AProjectile> ProjectileClass;

	FTimerHandle ProjectileAttackTimerHandle;

};
