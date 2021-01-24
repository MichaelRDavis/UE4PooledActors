// Fill out your copyright notice in the Description page of Project Settings.

#include "PooledProjectileComponent.h"
#include "PooledActorComponent.h"
#include "PooledProjectile.h"
#include "PooledActorGameInstance.h"
#include "PooledActorManager.h"

UPooledProjectileComponent::UPooledProjectileComponent()
{
	ProjectilePoolSize = 0;
}

void UPooledProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectilePoolSize > 0 && bAutoInitialize)
	{
		InitializeProjectilePool(ProjectilePoolSize);
	}
}

void UPooledProjectileComponent::InitializeProjectilePool(int32 InProjectilePoolSize)
{
	if (InProjectilePoolSize > 0)
	{
		ProjectilePoolSize = InProjectilePoolSize;

		for (int32 i = 0; i < ProjectilePoolSize; i++)
		{
			APooledProjectile* Projectile = GetWorld()->SpawnActor<APooledProjectile>();
			ProjectilePool.Add(Projectile);
		}
	}
}

APooledProjectile* UPooledProjectileComponent::SpawnPooledProjectile(TSubclassOf<APooledProjectile> ProjectileClass, FTransform SpawnTransform)
{
	for (APooledProjectile* Projectile : ProjectilePool)
	{
		if (Projectile && !Projectile->IsActive())
		{
			Projectile->ActivateActor();
			Projectile->SetOwningPool(Cast<UPooledActorComponent>(this));	// This is a dirty cast
			Projectile->SetActorTransform(SpawnTransform);
			Projectile->SetLifeSpan(5.0f);
			return Projectile;
		}
	}

	return nullptr;
}

