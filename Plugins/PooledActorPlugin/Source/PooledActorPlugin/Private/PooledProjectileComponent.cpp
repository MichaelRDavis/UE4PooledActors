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

	UPooledActorGameInstance* GameInst = Cast<UPooledActorGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst)
	{
		LocalPooledActorManager = GameInst->GetPooledActorManager();
		if (LocalPooledActorManager)
		{
			InitializeProjectilePool(ProjectilePoolSize);
		}
	}
}

void UPooledProjectileComponent::InitializeProjectilePool(int32 InProjectilePoolSize)
{
	if (InProjectilePoolSize > 0)
	{
		ProjectilePoolSize = InProjectilePoolSize;
		LocalPooledActorManager->AddActorsToPool(PooledProjectileClass, ProjectilePoolSize);
	}
}

APooledProjectile* UPooledProjectileComponent::SpawnPooledProjectile(TSubclassOf<APooledProjectile> ProjectileClass, FTransform SpawnTransform)
{
	APooledProjectile* Projectile = Cast<APooledProjectile>(LocalPooledActorManager->GetActorFromPool(ProjectileClass));
	if (Projectile != nullptr)
	{
		Projectile->SetOwningPool(Cast<UPooledActorComponent>(this));	// This is a dirty cast
		Projectile->SetActorTransform(SpawnTransform);
		Projectile->ActivateActor();
		return Projectile;
	}
	else
	{
		LocalPooledActorManager->AddActorsToPool(ProjectileClass, ProjectilePoolSize);
		APooledProjectile* NewProjectile = Cast<APooledProjectile>(LocalPooledActorManager->GetActorFromPool(ProjectileClass));
		if (NewProjectile != nullptr)
		{
			NewProjectile->ActivateActor();
			return NewProjectile;
		}
	}

	return nullptr;
}

