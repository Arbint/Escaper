// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawner.generated.h"

UCLASS()
class THEESCAPER_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere, Category = "PickupSpawner")
	class USceneComponent* RootComp;
	
	UPROPERTY(VisibleAnywhere, Category = "PickupSpawner")
	class USceneComponent* SpawnLoc;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TArray<TSubclassOf<class ATriggerable>> PickupClasses;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float spawnInterval = 2.f;
	
	FTimerHandle SpawnTimmerHandle;

	UFUNCTION()
	void OnPickupDestroied(AActor* Pickup);

	void SpawnPickup();
};
