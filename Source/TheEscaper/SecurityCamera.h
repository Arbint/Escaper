// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecurityCamera.generated.h"

UCLASS()
class THEESCAPER_API ASecurityCamera : public AActor
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
	class USpotLightComponent* sightRef;

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
