// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Triggerable.generated.h"
class UBoxComponent;
UCLASS()
class THEESCAPER_API ATriggerable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent, Category = "Trigger", Meta = (DisplayName = "OnTriggered"))
	void BP_OnTriggered(AActor* actor);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UBoxComponent* GetTriggerBox() const { return TriggerComp; }

private:
	UPROPERTY()
	class USceneComponent* rootComp;
	UPROPERTY(VisibleDefaultsOnly, Category = "Trigger")
	UBoxComponent* TriggerComp;

	UFUNCTION()
	void Overlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnded(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void OnTriggered(AActor* actor);
	virtual void OnActorLeftTrigger(AActor* actor);


};
