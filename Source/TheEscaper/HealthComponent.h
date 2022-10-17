// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float, health, float, delta, float, maxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthEmpty);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEESCAPER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthEmpty OnHealthEmpty;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	bool bFriendlyFire = false;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float health = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "MaxHealth")
	float maxHealth = 100.f;

	UFUNCTION()
	void TakenDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void ChangeHealth(float amt);
};
