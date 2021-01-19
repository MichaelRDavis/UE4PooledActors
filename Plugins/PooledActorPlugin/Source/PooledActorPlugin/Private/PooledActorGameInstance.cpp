// Fill out your copyright notice in the Description page of Project Settings.

#include "PooledActorGameInstance.h"
#include "PooledActorPlugin/Public/PooledActorManager.h"

UPooledActorGameInstance::UPooledActorGameInstance()
{
	PooledActorManagerClass = APooledActorManager::StaticClass();
}

void UPooledActorGameInstance::Init()
{
	Super::Init();

	if (PooledActorManagerClass)
	{
		PooledActorManager = GetWorld()->SpawnActor<APooledActorManager>();
	}
}

void UPooledActorGameInstance::Shutdown()
{
	Super::Shutdown();

	if (PooledActorManager)
	{
		PooledActorManager->RemoveActorsFromPool();
	}
}
