// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledActorComponent.generated.h"

class APooledActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POOLEDACTORPLUGIN_API UPooledActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPooledActorComponent();

	UFUNCTION(BlueprintCallable, Category=PooledActor)
	virtual void InitializeActorPool(int32 PoolSize);

	UFUNCTION(BlueprintCallable, Category=PooledActor)
	APooledActor* SpawnPooledActor(FTransform SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	TSubclassOf<APooledActor> PooledActorClass;

	UPROPERTY(BlueprintReadOnly, Category=PooledActor)
	TArray<APooledActor*> ActorPool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	int32 ActorPoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	bool bAutoInitialize;
};
