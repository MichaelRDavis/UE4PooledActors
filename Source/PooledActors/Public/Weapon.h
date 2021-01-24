// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UPooledProjectileComponent;

/**
 * You can create a PooledActorComponent's on other Actors, though this is not recommended due to their volatility.  
 * A best practice approach would be to store them on a persistent actor the persists for the lifecycle of the game e.g. the PlayerController class.
 */
UCLASS()
class POOLEDACTORS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pool")
	UPooledProjectileComponent* ProjectilePool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon: Ammo")
	int32 Ammo;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fire();
	void Fire_Implementation();
};
