// Fill out your copyright notice in the Description page of Project Settings.

#include "PooledProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

APooledProjectile::APooledProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(CollisionComp);
}

void APooledProjectile::BeginPlay()
{
	Super::BeginPlay();

	DeactivateActor();
}

void APooledProjectile::ActivateActor()
{
	Super::ActivateActor();

	CollisionComp->SetActive(true);
	ProjectileMovement->SetActive(true);
}

void APooledProjectile::DeactivateActor()
{
	Super::DeactivateActor();

	CollisionComp->SetActive(false);
	ProjectileMovement->SetActive(false);
}
