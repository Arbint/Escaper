// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "LazerGunComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEESCAPER_API ULazerGunComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULazerGunComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	bool LazerOn();

	void LazerOff();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "LazerGun")
	float Energy = 100;

	UPROPERTY(EditDefaultsOnly, Category = "LazerGun")
	float MaxEnergy = 100;

	UPROPERTY(EditDefaultsOnly, Category = "LazerGun")
	float RegenSpeed = 30;

	UPROPERTY(EditDefaultsOnly, Category = "LazerGun")
	float ConsumeSpeed = 80;

	UPROPERTY(EditDefaultsOnly, Category = "LazerGun")
	float EnergyConsumptionRate = 10;

	bool bIsLazerOn = false;

	void ConsumeEnergy(float DeltaTime);
	void RegenrateEnrgy(float DeltaTime);
};
