// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityCamera.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/SpotLightComponent.h"
#include "Components/SceneComponent.h"
// Sets default values
ASecurityCamera::ASecurityCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PercpetionComp");
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);

	sightRef = CreateDefaultSubobject<USpotLightComponent>("SigthRef");
	sightRef->SetupAttachment(RootComp);

	
	if (sightConfig)
	{
		PerceptionComp->ConfigureSense(*sightConfig);
	}
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ASecurityCamera::PerceptionUpdated);
}

// Called when the game starts or when spawned
void ASecurityCamera::BeginPlay()
{
	Super::BeginPlay();
	sightConfig->SightRadius = sightRef->AttenuationRadius;
	sightConfig->LoseSightRadius = sightRef->AttenuationRadius;
	sightConfig->PeripheralVisionAngleDegrees = sightRef->OuterConeAngle;
}

// Called every frame
void ASecurityCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASecurityCamera::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
}

