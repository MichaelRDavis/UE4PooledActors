// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledActorComponent.generated.h"

class APooledActor;
class APooledActorManager;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POOLEDACTORPLUGIN_API UPooledActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPooledActorComponent();

	virtual void BeginPlay() override;
	virtual void DestroyComponent(bool bPromoteChildren /* = false */) override;

	/** Initialize owned actor pool */
	UFUNCTION(BlueprintCallable, Category=PooledActor)
	virtual void InitializeActorPool(int32 PoolSize);

	/** Add a pooled actor to owned actor pool */
	UFUNCTION(BlueprintCallable, Category=PooledActor)
	void AddOwnedActorsToPool(APooledActor* Actor);

	/** Returns owned pooled actors to owned actor pool */
	UFUNCTION(BlueprintCallable, Category=PooledActor)
	void ReturnOwnedActorsToPool();

	/** Returns a owned pooled actor to the owning pool */
	void ReturnToOwningActorPool(APooledActor* Actor);

	/** Spawns a pooled actor from the owned actor pool */
	UFUNCTION(BlueprintCallable, Category=PooledActor)
	APooledActor* SpawnPooledActor(TSubclassOf<APooledActor> PooledActor, FTransform SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner);

protected:
	/** Class of pooled actor to spawn in actor pool */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	TSubclassOf<APooledActor> PooledActor;

	/** Number of pooled actors to store within actor pool */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	int32 ActorPoolSize;

	/** True if actor pool should initialize pool when begin play is called for this component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	bool bAutoInitialize;

private:
	/** List of pooled actors owned by this pool */
	UPROPERTY()
	TArray<APooledActor*> OwnedActorPool; 

	/** Cached pointer to the pooled actor manager class */
	UPROPERTY()
	APooledActorManager* LocalPooledActorManager;
};
