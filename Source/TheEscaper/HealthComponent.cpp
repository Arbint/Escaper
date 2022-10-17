// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Perception/AISense_Damage.h"
#include "GenericTeamAgentInterface.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakenDamage);
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakenDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (FGenericTeamId::GetAttitude(GetOwner(), DamageCauser) == ETeamAttitude::Friendly && !bFriendlyFire)
		return;

	if (Damage == 0)
		return;

	if (Damage > 0)
	{
		UAISense_Damage::ReportDamageEvent(this, GetOwner(), DamageCauser, Damage, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation());
	}
	
	ChangeHealth(-Damage);
}

void UHealthComponent::ChangeHealth(float amt)
{
	if (amt == 0) return;
	health = FMath::Clamp(health + amt, 0, maxHealth);
	OnHealthChanged.Broadcast(health, amt, maxHealth);
	if (health == 0)
	{
		OnHealthEmpty.Broadcast();
	}
}

