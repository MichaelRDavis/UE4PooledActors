// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PooledActorGameInstance.generated.h"

class APooledActorManager;

UCLASS()
class POOLEDACTORPLUGIN_API UPooledActorGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPooledActorGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	inline APooledActorManager* GetPooledActorManager() const
	{
		return PooledActorManager;
	}

private:
	UPROPERTY()
	TSubclassOf<APooledActorManager> PooledActorManagerClass;

	UPROPERTY()
	APooledActorManager* PooledActorManager;
};
