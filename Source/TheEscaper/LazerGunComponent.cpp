// Fill out your copyright notice in the Description page of Project Settings.


#include "LazerGunComponent.h"

// Sets default values for this component's properties
ULazerGunComponent::ULazerGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULazerGunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool ULazerGunComponent::LazerOn()
{
	if (!bIsLazerOn)
	{
		if (Energy > 10)
		{
			bIsLazerOn = true;
		}
	}
	return bIsLazerOn;
}

void ULazerGunComponent::LazerOff()
{
	bIsLazerOn = false;
}

void ULazerGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (bIsLazerOn)
	{
		ConsumeEnergy(DeltaTime);
	}
	else if(Energy < MaxEnergy)
	{
		RegenrateEnrgy(DeltaTime);
	}
}

void ULazerGunComponent::ConsumeEnergy(float DeltaTime)
{
	Energy -= DeltaTime * ConsumeSpeed;
	if (Energy <= 0)
	{
		Energy = 0;
		bIsLazerOn = false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Consuming Energy is now: %f"), Energy);
}

void ULazerGunComponent::RegenrateEnrgy(float DeltaTime)
{
	Energy += DeltaTime * RegenSpeed;
	if (Energy >= MaxEnergy)
	{
		Energy = MaxEnergy;
	}
	UE_LOG(LogTemp, Warning, TEXT("Regernating Energy is now: %f"), Energy);
}


