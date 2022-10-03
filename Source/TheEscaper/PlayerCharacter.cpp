// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

APlayerCharacter::APlayerCharacter()
{
	playerEye = CreateDefaultSubobject<UCameraComponent>("playerEye");
	playerEye->SetupAttachment(GetRootComponent());
	playerEye->bUsePawnControlRotation = true;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction("nextWeapon", IE_Pressed, this, &APlayerCharacter::NextWeapon);
	PlayerInputComponent->BindAction("prevWeapon", IE_Pressed, this, &APlayerCharacter::PrevWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->AttachToComponent(playerEye, FAttachmentTransformRules::KeepWorldTransform);
}

void APlayerCharacter::MoveForward(float amt)
{
	AddMovementInput(GetActorForwardVector() * amt);
}

void APlayerCharacter::MoveRight(float amt)
{
	AddMovementInput(GetActorRightVector() * amt);
}

void APlayerCharacter::Turn(float amt)
{
	AddControllerYawInput(amt);
}

void APlayerCharacter::LookUp(float amt)
{
	AddControllerPitchInput(amt);
}
