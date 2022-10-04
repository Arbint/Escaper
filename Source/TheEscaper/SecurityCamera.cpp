// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityCamera.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/SpotLightComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "EPlayerController.h"
// Sets default values
ASecurityCamera::ASecurityCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);

	RotationPivot = CreateDefaultSubobject<USceneComponent>("RotationPivot");
	RotationPivot->SetupAttachment(RootComp);
	
	sightRef = CreateDefaultSubobject<USpotLightComponent>("SigthRef");
	sightRef->SetupAttachment(RotationPivot);

	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PercpetionComp");
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	if (PerceptionComp && sightConfig)
	{
		sightConfig->DetectionByAffiliation.bDetectEnemies = true;
		sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		PerceptionComp->ConfigureSense(*sightConfig);
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ASecurityCamera::AIPerceptionUpdated);
	}
}

// Called when the game starts or when spawned
void ASecurityCamera::BeginPlay()
{
	Super::BeginPlay();
	sightRef->SetLightColor(NeutralColor);
	if (sightConfig && PerceptionComp && sightRef)
	{
		sightConfig->SightRadius = sightRef->AttenuationRadius;
		sightConfig->LoseSightRadius = sightRef->AttenuationRadius;
		sightConfig->PeripheralVisionAngleDegrees = sightRef->OuterConeAngle;
		PerceptionComp->ConfigureSense(*sightConfig);
	}

	RotationDuration = yawHalfRange / yawSpeed * 2.f;
	
	yawDir = 1;
	RotationPivot->SetRelativeRotation(FRotator(0, -yawDir * yawHalfRange, 0));

	GetWorldTimerManager().SetTimer(yawTimerHandle, this, &ASecurityCamera::ReverseDir, RotationDuration, true);
}

// Called every frame
void ASecurityCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float currentYaw = RotationPivot->GetRelativeRotation().Yaw;
	float goalYaw = currentYaw + yawDir * yawSpeed * DeltaTime;
	RotationPivot->SetRelativeRotation(FRotator(0,goalYaw,0));
}

void ASecurityCamera::ReverseDir()
{
	yawDir *= -1;
}

void ASecurityCamera::AIPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AEPlayerController* playerController = Cast<AEPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (Actor->GetOwner() == playerController)
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			sightRef->SetLightColor(DetectedColor);
			yawDir = 0.f;
			playerController->Caught();
		}
		else
		{
			sightRef->SetLightColor(NeutralColor);
		}
	}
}

void ASecurityCamera::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = sightRef->GetComponentLocation();
	OutRotation = sightRef->GetComponentRotation();
}
