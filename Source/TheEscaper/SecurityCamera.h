// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Perception/AIPerceptionComponent.h"
#include "SecurityCamera.generated.h"

UCLASS()
class THEESCAPER_API ASecurityCamera : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASecurityCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "AIPerception")
	class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY()
	class UAISenseConfig_Sight* sightConfig;

	UPROPERTY(VisibleAnywhere, Category = "AIPerception")
	class USceneComponent* RootComp;
	
	UPROPERTY(VisibleAnywhere, Category = "AIPerception")
	class USceneComponent* RotationPivot;

	UPROPERTY(VisibleAnywhere, Category = "AIPerception")
	class USpotLightComponent* sightRef;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	float yawSpeed = 5.f;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	float pauseTime = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float yawHalfRange = 30.f;

	float yawDir;

	FTimerHandle yawTimerHandle;
	float RotationDuration;
	void ReverseDir();

	UFUNCTION()
	void AIPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

};
