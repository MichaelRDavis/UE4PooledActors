// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledProjectileComponent.generated.h"

class APooledProjectile;
class APooledActorManager;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POOLEDACTORPLUGIN_API UPooledProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPooledProjectileComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category=PooledProjectile)
	void InitializeProjectilePool(int32 InProjectilePoolSize);

	UFUNCTION(BlueprintCallable, Category=PooledProjectile)
	APooledProjectile* SpawnPooledProjectile(TSubclassOf<APooledProjectile> ProjectileClass, FTransform SpawnTransform);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=PooledProjectile)
	TArray<APooledProjectile*> ProjectilePool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledProjectile)
	TSubclassOf<APooledProjectile> PooledProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledProjectile)
	int32 ProjectilePoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PooledProjectile)
	bool bAutoInitialize;
};
