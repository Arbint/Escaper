// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "Kismet/GameplayStatics.h"

AHealthPickup::AHealthPickup()
{
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(GetRootComponent());
}

void AHealthPickup::OnTriggered(AActor* actor)
{
	UGameplayStatics::ApplyDamage(actor, healAmount * -1, nullptr, this, nullptr);
	Destroy();
}

void AHealthPickup::OnActorLeftTrigger(AActor* actor)
{
}
