// Fill out your copyright notice in the Description page of Project Settings.


#include "ECharacterBase.h"

// Sets default values
AECharacterBase::AECharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AECharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AECharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AECharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AECharacterBase::Attack()
{
	//ask the blueprint to play a montage
	GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
}

