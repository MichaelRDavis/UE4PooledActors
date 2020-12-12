// Fill out your copyright notice in the Description page of Project Settings.

#include "PooledActorComponent.h"
#include "PooledActor.h"

UPooledActorComponent::UPooledActorComponent()
{
	ActorPoolSize = 0;
	bAutoInitialize = false;
}

void UPooledActorComponent::InitializeActorPool(int32 PoolSize)
{
	if (PooledActorClass)
	{
		for (int32 i = 0; i < ActorPoolSize; i++)
		{
			APooledActor* Actor = GetWorld()->SpawnActor<APooledActor>(PooledActorClass);
			if (Actor)
			{
				ActorPool.Add(Actor);
			}
		}
	}
}

APooledActor* UPooledActorComponent::SpawnPooledActor(FTransform SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner)
{
	for (APooledActor* Actor : ActorPool)
	{
		if (Actor != nullptr && Actor->IsActive())
		{
			Actor->SetActorTransform(SpawnTransform);
			Actor->SpawnCollisionHandlingMethod = CollisionHandlingOverride;
			Actor->SetOwner(Owner);
			Actor->ActivateActor();
			return Actor;
		}
	}

	return nullptr;
}
