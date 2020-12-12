// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PooledActor.h"
#include "PooledProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class POOLEDACTORPLUGIN_API APooledProjectile : public APooledActor
{
	GENERATED_BODY()
	
public:
	APooledProjectile();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Projectile, meta=(AllowPrivateAccess="true"))
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Projectile, meta=(AllowPrivateAccess="true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	USphereComponent* GetCollisionComp() const {return CollisionComp;}

	UProjectileMovementComponent* GetProjectileMovement() const {return ProjectileMovement;}
};
