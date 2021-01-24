// Fill out your copyright notice in the Description page of Project Settings.

#include "PooledActorComponent.h"
#include "PooledActor.h"

UPooledActorComponent::UPooledActorComponent()
{
	ActorPoolSize = 0;
	bAutoInitialize = false;
}

void UPooledActorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ActorPoolSize > 0 && bAutoInitialize)
	{
		InitializeActorPool(ActorPoolSize);
	}
}

void UPooledActorComponent::DestroyComponent(bool bPromoteChildren /* = false */)
{
	Super::DestroyComponent(bPromoteChildren);
}

void UPooledActorComponent::InitializeActorPool(int32 PoolSize)
{
	if (PoolSize > 0)
	{
		ActorPoolSize = PoolSize;

		for (int32 i = 0; i < ActorPoolSize; i++)
		{
			APooledActor* Actor = GetWorld()->SpawnActor<APooledActor>();
			OwnedActorPool.Add(Actor);
		}
	}
}

APooledActor* UPooledActorComponent::SpawnPooledActor(TSubclassOf<APooledActor> PooledActorClass, FTransform SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner)
{
	for (APooledActor* Actor : OwnedActorPool)
	{
		Actor->ActivateActor();
		Actor->SetActorTransform(SpawnTransform);
		Actor->SetOwner(Owner);
		return Actor;
	}

	return nullptr;
}
