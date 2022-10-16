// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"
#include "PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Weapon.h"
AWeaponPickup::AWeaponPickup()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(GetRootComponent());
}

void AWeaponPickup::SetRandomWeapon()
{
	if(weaponClasses.Num() > 0)
	{
		int randomNum = FMath::RandRange(0, weaponClasses.Num() - 1);
		WeaponClass = weaponClasses[randomNum];
		MeshComp->SetStaticMesh(WeaponClass.GetDefaultObject()->GetMesh());
	}
}

void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponClass)
	{
		MeshComp->SetStaticMesh(WeaponClass.GetDefaultObject()->GetMesh());
	}
}

void AWeaponPickup::OnTriggered(AActor* actor)
{
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(actor);
	if (playerCharacter)
	{
		playerCharacter->GiveWeapon(WeaponClass);
		Destroy();
	}
}

#if WITH_EDITOR
void AWeaponPickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.Property)
	{
		const FName changedPropertyName = PropertyChangedEvent.GetPropertyName();
		const FName weaponClassPropName = GET_MEMBER_NAME_CHECKED(AWeaponPickup, WeaponClass);
		if (changedPropertyName == weaponClassPropName)
		{
			if (WeaponClass)
			{
				MeshComp->SetStaticMesh(WeaponClass.GetDefaultObject()->GetMesh());
			}
		}
	}
}
#endif //WITH_EDITOR