// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(RootComp);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::OnAquired(class USkeletalMeshComponent* OwnerMesh)
{
	OwnerSkeletalMesh = OwnerMesh;
	SetActorHiddenInGame(true);
	AttachToComponent(OwnerSkeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
}

void AWeapon::Attack()
{
	if (CanAttack())
	{
		GetWorldTimerManager().SetTimer(FiringTimmer, 1/firingRate, false);
		OwnerSkeletalMesh->GetAnimInstance()->Montage_Play(AttackMontage);
	}
}

void AWeapon::GetAnims(UAnimSequence*& Idle, UAnimSequence*& Walk, UAnimMontage*& Attack) const
{
	Idle = IdleAnim;
	Walk = WalkAnim;
	Attack = AttackMontage;
}

bool AWeapon::GetAmmoStatus(int& OutAmmoInClip, int& OutAmmoInInventory) const
{
	return false;
}

void AWeapon::AttackPointAnimNotify()
{
	UE_LOG(LogTemp, Warning, TEXT("Committing attack"));
}

void AWeapon::Reload()
{

}

void AWeapon::BackToInventory()
{
	SetActorHiddenInGame(true);
	OnBackToInventory();
}

void AWeapon::PutInHand()
{
	SetActorHiddenInGame(false);
	OnPutInHand();
}

bool AWeapon::CanAttack() const
{
	return !GetWorldTimerManager().IsTimerActive(FiringTimmer);
}

void AWeapon::OnBackToInventory()
{
}

void AWeapon::OnPutInHand()
{
}

