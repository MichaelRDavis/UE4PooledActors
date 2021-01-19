// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActorManager.generated.h"

class APooledActor;

UCLASS()
class POOLEDACTORPLUGIN_API APooledActorManager : public AActor
{
	GENERATED_BODY()

public:
	APooledActorManager();

	void AddActorsToPool(TSubclassOf<APooledActor> ActorClass, int32 ActorSize);

	void ReturnActorsToPool(APooledActor* PooledActor);

	void RemoveActorsFromPool();
	
	APooledActor* GetActorFromPool(TSubclassOf<APooledActor> ActorClass);

	bool DoesActorExistInPool(TSubclassOf<APooledActor> ActorClass) const;

private:
	UPROPERTY()
	TArray<APooledActor*> ActorPool;
};
