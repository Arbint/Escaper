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

	//update the animations based on the mesh
	USkeletalMesh* mesh = OwnerMesh->SkeletalMesh;

	AttackMontage = ReloadMontage = nullptr;
	IdleAnim = WalkAnim = nullptr;
	
	if (AttackMontageMap.Contains(mesh))
		AttackMontage = AttackMontageMap[mesh];

	if (ReoloadMontageMap.Contains(mesh))
		ReloadMontage = ReoloadMontageMap[mesh];

	if (IdleAnimMap.Contains(mesh))
		IdleAnim = IdleAnimMap[mesh];

	if (WalkAnimMap.Contains(mesh))
		WalkAnim = WalkAnimMap[mesh];
}

void AWeapon::ReplenishAmmo(int amt)
{
}

void AWeapon::Attack()
{
	if (CanAttack())
	{
		GetWorldTimerManager().SetTimer(FiringTimmer, 1/firingRate, false);
		OwnerSkeletalMesh->GetAnimInstance()->Montage_Play(AttackMontage);
	}
}

void AWeapon::Reload()
{
}

void AWeapon::PutInInventory()
{
	SetActorHiddenInGame(true);
	bIsActiveWeapon = false;
}

void AWeapon::PutInHand()
{
	SetActorHiddenInGame(false);
	bIsActiveWeapon = true;
}

void AWeapon::GetAnims(UAnimSequence*& Idle, UAnimSequence*& Walk, UAnimMontage*& Attack) const
{
	Idle = IdleAnim;
	Walk = WalkAnim;
	Attack = AttackMontage;
}

void AWeapon::AttackPointAnimNotify()
{
}

bool AWeapon::GetAmmoStatus(int& clipAmmo, int& inventoryAmmo) const
{
	return false;
}

bool AWeapon::CanAttack() const
{
	return !GetWorldTimerManager().IsTimerActive(FiringTimmer);
}

