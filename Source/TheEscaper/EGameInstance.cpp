// Fill out your copyright notice in the Description page of Project Settings.


#include "EGameInstance.h"
#include "WeaponDataManager.h"

// Sets default values
AEGameInstance::AEGameInstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponDataManager = CreateDefaultSubobject<UWeaponDataManager>("WeaponDataManager");
}

// Called when the game starts or when spawned
void AEGameInstance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEGameInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

