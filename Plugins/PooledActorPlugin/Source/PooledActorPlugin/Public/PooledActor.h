// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

UCLASS()
class POOLEDACTORPLUGIN_API APooledActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APooledActor();

	virtual void BeginPlay() override;

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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	float PooledActorLifespan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledActor)
	bool bAutoActivate;
};