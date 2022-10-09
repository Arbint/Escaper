// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"
#include "PlayerCharacter.h"
#include "Weapon.h"
#include "Components/BoxComponent.h"

#define ECC_Character ECC_GameTraceChannel1

AWeaponPickup::AWeaponPickup()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	mesh->SetupAttachment(GetRootComponent());
	GetTriggerBox()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetTriggerBox()->SetCollisionResponseToChannel(ECC_Character, ECR_Overlap);
}
void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	if (weaponClass)
	{
		mesh->SetStaticMesh(weaponClass.GetDefaultObject()->GetWeaponMesh());
	}
}
void AWeaponPickup::OnTriggered(AActor* actor)
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(actor);
	if (PC != nullptr)
	{
		PC->GiveWeapon(weaponClass);
		Destroy();
	}
}

void AWeaponPickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.Property != nullptr)
	{
		const FName ChangedPropName = PropertyChangedEvent.GetPropertyName();
		const FName weaponClassName = GET_MEMBER_NAME_CHECKED(AWeaponPickup, weaponClass);
		if (ChangedPropName == weaponClassName && weaponClass!=nullptr)
		{
			mesh->SetStaticMesh(weaponClass.GetDefaultObject()->GetWeaponMesh());
		}
	}
}
