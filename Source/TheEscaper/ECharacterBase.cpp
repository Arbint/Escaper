// Fill out your copyright notice in the Description page of Project Settings.


#include "ECharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Weapon.h"
#include "HealthComponent.h"

#define ECC_Character ECC_GameTraceChannel1
// Sets default values
AECharacterBase::AECharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Character);
	healthComp = CreateDefaultSubobject<UHealthComponent>("healthComp");
	healthComp->OnHealthChanged.AddDynamic(this, &AECharacterBase::HealthChanged);
	healthComp->OnHealthEmpty.AddDynamic(this, &AECharacterBase::StartDeathSequence);
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

void AECharacterBase::GiveWeapon(TSubclassOf<AWeapon> weaponClass)
{
	if (HasWeaponOfType(weaponClass))
	{
		//TODO: maybe add ammo here
		return;
	}
	AWeapon* newWeapon = GetWorld()->SpawnActor<AWeapon>(weaponClass);
	newWeapon->SetOwner(this);
	newWeapon->OnAquired(GetMesh());
	weapons.Add(newWeapon);
	OnWeaponGiven.Broadcast(newWeapon);
	if (currentWeapon == nullptr)
	{
		EquipWeapon(weapons.Num() - 1);
	}
}

// Called to bind functionality to input
void AECharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AECharacterBase::Attack()
{
	if (currentWeapon != nullptr && !GetWorldTimerManager().IsTimerActive(WeaponSwitchingHandle))
	{
		currentWeapon->Attack();
	}
}

void AECharacterBase::PrevWeapon()
{
	if (weapons.Num() <= 0)
		return;

	int prevIndex = weaponIndex - 1;
	if (prevIndex < 0)
	{
		prevIndex = weapons.Num() - 1;
	}
	EquipWeapon(prevIndex);
}

void AECharacterBase::NextWeapon()
{
	if (weapons.Num() <= 0)
		return;

	int nextIndex = weaponIndex + 1;
	if (nextIndex >= weapons.Num())
	{
		nextIndex = 0;
	}
	EquipWeapon(nextIndex);
}

void AECharacterBase::Reload()
{
	if (currentWeapon)
	{
		currentWeapon->Reload();
	}
}

bool AECharacterBase::HasWeaponOfType(TSubclassOf<AWeapon> weaponClass) const
{
	for (AWeapon* weapon : weapons)
	{
		if (weapon->GetClass() == weaponClass)
		{
			return true;
		}
	}
	return false;
}

void AECharacterBase::EquipWeapon(int index)
{
	//do nothing if same weapon
	if (currentWeapon == weapons[index])
		return;

	float SwitchDuration = GetMesh()->GetAnimInstance()->Montage_Play(WeaponSwitchMontage);

	weaponIndex = index;
	GetWorldTimerManager().SetTimer(WeaponSwitchingHandle, this, &AECharacterBase::WeaponSwitchTimePoint, SwitchDuration/2, false);
	
}

void AECharacterBase::HealthChanged(float val, float delta, float maxVal)
{
	OnHealthChange(val, delta, maxVal);
}

void AECharacterBase::StartDeathSequence()
{
	if (!bIsDead)
	{
		bIsDead = true;
		OnDeathStarted();
		DisableGameplayRelavency();
		for (auto weapon : weapons)
		{
			weapon->Destroy();
		}

		if (DeathMontage)
		{
			float deathAnimDuration = GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage);
			GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AECharacterBase::Dead, deathAnimDuration + 1, false);
		}
	}
}

void AECharacterBase::OnHealthChange(float val, float delta, float maxVal) { }

void AECharacterBase::OnDeathStarted() { }

void AECharacterBase::Dead()
{
	Destroy();
}

void AECharacterBase::DisableGameplayRelavency()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AECharacterBase::WeaponSwitchTimePoint()
{
	if (currentWeapon)
	{
		currentWeapon->PutInInventory();
	}
	currentWeapon = weapons[weaponIndex];
	currentWeapon->PutInHand();
	OnWeaponSwitched.Broadcast(currentWeapon);
}