// Fill out your copyright notice in the Description page of Project Settings.

#include "PooledActorComponent.h"
#include "PooledActor.h"
#include "PooledActorGameInstance.h"
#include "PooledActorManager.h"

UPooledActorComponent::UPooledActorComponent()
{
	ActorPoolSize = 0;
	bAutoInitialize = false;
}

void UPooledActorComponent::BeginPlay()
{
	Super::BeginPlay();

	UPooledActorGameInstance* GameInst = Cast<UPooledActorGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst)
	{
		LocalPooledActorManager = GameInst->GetPooledActorManager();
		if (LocalPooledActorManager)
		{
			if (bAutoInitialize)
			{
				InitializeActorPool(ActorPoolSize);
			}
		}
	}
}

void UPooledActorComponent::DestroyComponent(bool bPromoteChildren /* = false */)
{
	Super::DestroyComponent(bPromoteChildren);

	// Returns pooled actors to main actor pool when this component is destroyed
	if (LocalPooledActorManager)
	{
		ReturnOwnedActorsToPool();
	}
}

void UPooledActorComponent::InitializeActorPool(int32 PoolSize)
{
	ActorPoolSize = PoolSize;

	// Only initialize owned actor pool if pooled actor can not be found within the actor pool manager
	if (PooledActor != nullptr && LocalPooledActorManager != nullptr && PoolSize > 0 && !LocalPooledActorManager->DoesActorExistInPool(PooledActor))
	{
		// Add pooled actors to actor pool manager, because they do not exit within actor pool manager
		LocalPooledActorManager->AddActorsToPool(PooledActor, PoolSize);
		
		// Grab pooled actors from the pooled actor manager class
		for (int32 i = 0; i < PoolSize; i++)
		{
			AddOwnedActorsToPool(LocalPooledActorManager->GetActorFromPool(PooledActor));
		}
	}

	// If they already exist then just grab them from the actor pool manager
	if (PooledActor != nullptr && LocalPooledActorManager->DoesActorExistInPool(PooledActor))
	{
		// Grab pooled actors from the pooled actor manager class
		for (int32 i = 0; i < PoolSize; i++)
		{
			AddOwnedActorsToPool(LocalPooledActorManager->GetActorFromPool(PooledActor));
		}
	}
}

void UPooledActorComponent::AddOwnedActorsToPool(APooledActor* Actor)
{
	if (Actor)
	{
		OwnedActorPool.Reserve(ActorPoolSize);
		OwnedActorPool.Add(Actor);
	}
}

void UPooledActorComponent::ReturnOwnedActorsToPool()
{
	for (int32 i = 0; i < OwnedActorPool.Num(); i++)
	{
		LocalPooledActorManager->ReturnActorsToPool(OwnedActorPool[i]);
	}
}

void UPooledActorComponent::ReturnToOwningActorPool(APooledActor* Actor)
{
	if (Actor)
	{
		OwnedActorPool.Add(Actor);
	}
}

APooledActor* UPooledActorComponent::SpawnPooledActor(TSubclassOf<APooledActor> PooledActorClass, FTransform SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner)
{
	if (LocalPooledActorManager)
	{
		APooledActor* Actor = LocalPooledActorManager->GetActorFromPool(PooledActorClass);
		Actor->SetOwner(Owner);
		return Actor;
	}

	return nullptr;
}
