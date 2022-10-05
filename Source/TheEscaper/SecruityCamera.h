// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Perception/AIPerceptionTypes.h"

#include "SecruityCamera.generated.h"

UCLASS()
class THEESCAPER_API ASecruityCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASecruityCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "AIPercepiton")
	void StopMoving();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "AIPercepiton")
	FORCEINLINE USceneComponent* GetYawPivot() const { return RotationYawPivot; }
	
	UFUNCTION(BlueprintCallable, Category = "AIPercepiton")
	FORCEINLINE USceneComponent* GetPitchPivot() const { return RotationPitchPivot; }
	
	UFUNCTION(BlueprintCallable, Category = "AIPercepiton")
	FORCEINLINE class UAIPerceptionComponent* GetPerceptionComp() const { return PerceptionComp; }

	UFUNCTION(BlueprintCallable, Category = "AIPercepiton")
	void SetLightColor(const FLinearColor& color);
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "AIPerception")
	class USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "AIPerception")
	class USceneComponent* RotationYawPivot;

	UPROPERTY(VisibleDefaultsOnly, Category = "AIPerception")
	class USceneComponent* RotationPitchPivot;

	UPROPERTY(VisibleDefaultsOnly, Category = "AIPerception")
	class  USpotLightComponent* CameraLight;

	UPROPERTY(VisibleDefaultsOnly, Category = "AIPerception")
	class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	UPROPERTY(EditDefaultsOnly, Category = "AIPerception")
	FLinearColor NeutralColor{0,1,0,1};
	
	UPROPERTY(EditDefaultsOnly, Category = "AIPerception")
	FLinearColor AlertColor{1,0,0,1};
};
