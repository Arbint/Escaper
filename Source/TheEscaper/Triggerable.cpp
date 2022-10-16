// Fill out your copyright notice in the Description page of Project Settings.


#include "Triggerable.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
ATriggerable::ATriggerable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootComp = CreateDefaultSubobject<USceneComponent>("rootComp");
	SetRootComponent(rootComp);

	TriggerComp = CreateDefaultSubobject<UBoxComponent>("TriggerComp");
	TriggerComp->SetupAttachment(rootComp);
	TriggerComp->OnComponentBeginOverlap.AddDynamic(this, &ATriggerable::Overlapped);
	TriggerComp->OnComponentEndOverlap.AddDynamic(this, &ATriggerable::OverlapEnded);
}

// Called when the game starts or when spawned
void ATriggerable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerable::Overlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnTriggered(OtherActor);
}

void ATriggerable::OverlapEnded(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnActorLeftTrigger(OtherActor);
}

void ATriggerable::OnTriggered(AActor* actor)
{
}

void ATriggerable::OnActorLeftTrigger(AActor* actor)
{
}

