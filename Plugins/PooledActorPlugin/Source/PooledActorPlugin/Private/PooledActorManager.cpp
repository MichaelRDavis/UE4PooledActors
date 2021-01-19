// Fill out your copyright notice in the Description page of Project Settings.

#include "PooledActorManager.h"
#include "PooledActor.h"

APooledActorManager::APooledActorManager()
{

}

void APooledActorManager::AddActorsToPool(TSubclassOf<APooledActor> ActorClass, int32 ActorSize)
{
	if (ActorClass != nullptr && ActorSize > 0)
	{
		for (int32 i = 0; i < ActorSize; i++)
		{
			APooledActor* Actor = GetWorld()->SpawnActor<APooledActor>(ActorClass);
			if (Actor)
			{
				Actor->DeactivateActor();
				ActorPool.Add(Actor);
			}
		}
	}
}

void APooledActorManager::ReturnActorsToPool(APooledActor* PooledActor)
{
	PooledActor->DeactivateActor();
	ActorPool.Add(PooledActor);
}

void APooledActorManager::RemoveActorsFromPool()
{
	for (int32 i = ActorPool.Num(); i < ActorPool.Num() - 1; i++)
	{
		ActorPool.Remove(ActorPool[i]);
		ActorPool[i]->Destroy();
	}
}

APooledActor* APooledActorManager::GetActorFromPool(TSubclassOf<APooledActor> ActorClass)
{
	for (int32 i = 0; i < ActorPool.Num(); i++)
	{
		if (ActorPool[i] && ActorPool[i]->IsA(ActorClass))
		{
			ActorPool[i]->ActivateActor();
			return ActorPool[i];
		}
	}

	return nullptr;
}

bool APooledActorManager::DoesActorExistInPool(TSubclassOf<APooledActor> ActorClass) const
{
	for (int32 i = 0; i < ActorPool.Num(); i++)
	{
		if (ActorPool[i] && ActorPool[i]->IsA(ActorClass))
		{
			return true;
		}
	}

	return false;
}
