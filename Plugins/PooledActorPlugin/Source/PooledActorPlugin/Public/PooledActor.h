// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

class UPooledActorComponent;

UCLASS()
class POOLEDACTORPLUGIN_API APooledActor : public AActor
{
	GENERATED_BODY()
	
public:		
	APooledActor();

	virtual void BeginPlay() override;
	virtual void Destroyed() override;
 	virtual void SetLifeSpan(float InLifespan) override;

	UFUNCTION(BlueprintCallable, Category=PooledActor)
	virtual void ActivateActor();

	UFUNCTION(BlueprintCallable, Category=PooledActor)
	virtual void DeactivateActor();

	UFUNCTION(BlueprintCallable, Category=PooledActor)
	void SetIsActive(bool bNewActive);

	UFUNCTION(BlueprintCallable, Category=PooledActor)
	void SetAutoActivate(bool bNewAutoActivate);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category=PooledActor)
	bool IsActive() const;

	void ReturnToOwningPool();

	void SetOwningPool(UPooledActorComponent* NewOnwer);

	inline UPooledActorComponent* GetOwningPool() const
	{
		return OwningPool;
	}

private:
	FTimerHandle LifespanHandle;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	float PooledActorLifespan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	bool bAutoActivate;

	/** True if this pooled actor is an orphan i.e. it's owning pool is destroyed */
	UPROPERTY()
	bool bIsOrphaned;

private:
	UPROPERTY()
	UPooledActorComponent* OwningPool;
};
