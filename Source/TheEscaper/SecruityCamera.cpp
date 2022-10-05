// Fill out your copyright notice in the Description page of Project Settings.


#include "SecruityCamera.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EPlayerController.h"

// Sets default values
ASecruityCamera::ASecruityCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);

	RotationYawPivot = CreateDefaultSubobject<USceneComponent>("RotationYawPivot");
	RotationYawPivot->SetupAttachment(RootComp);
	
	RotationPitchPivot = CreateDefaultSubobject<USceneComponent>("RotationPitchPivot");
	RotationPitchPivot->SetupAttachment(RotationYawPivot);

	CameraLight = CreateDefaultSubobject<USpotLightComponent>("CameraLight");
	CameraLight->SetupAttachment(RotationPitchPivot);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");

	if (SightConfig && PerceptionComp)
	{
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->SightRadius = 1500.f;
		SightConfig->PeripheralVisionAngleDegrees = 45.f;

		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ASecruityCamera::PerceptionUpdated);
	}
}

// Called when the game starts or when spawned
void ASecruityCamera::BeginPlay()
{
	Super::BeginPlay();
	SightConfig->SightRadius = CameraLight->AttenuationRadius;
	SightConfig->LoseSightRadius = CameraLight->AttenuationRadius;
	SightConfig->PeripheralVisionAngleDegrees = CameraLight->OuterConeAngle;
	PerceptionComp->ConfigureSense(*SightConfig);
	CameraLight->SetLightColor(NeutralColor);
}

// Called every frame
void ASecruityCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASecruityCamera::SetLightColor(const FLinearColor& color)
{
	CameraLight->SetLightColor(color);
}

void ASecruityCamera::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		CameraLight->SetLightColor(AlertColor);
		AEPlayerController* pc = Cast<AEPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		if (Actor->GetOwner() == pc)
		{
			pc->Caught();
			StopMoving();
		}
	}
}

void ASecruityCamera::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	//ai calls this function to get the view location and rotation for the sight
	OutLocation = CameraLight->GetComponentLocation();
	OutRotation = CameraLight->GetComponentRotation();
}

