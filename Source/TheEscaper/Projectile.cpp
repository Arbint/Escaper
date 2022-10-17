// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	projectileMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectileMesh;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));


}

void AProjectile::SetMaxSpeed(float speed)
{
	ProjectileMovementComponent->MaxSpeed = speed;
}

void AProjectile::SetInitialSpeed(float speed)
{
	ProjectileMovementComponent->InitialSpeed = speed;
}

void AProjectile::SetDamage(float Damage)
{
	damage = Damage;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor && OtherActor != this)
	{
		TArray<AActor*> igonredActors{GetOwner()};
		UGameplayStatics::ApplyRadialDamage(this, damage, GetActorLocation(), damageRadius, nullptr, igonredActors, GetOwner());
	}
	Destroy();
}

