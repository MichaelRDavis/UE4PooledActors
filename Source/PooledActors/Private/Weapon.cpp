// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "PooledActorPlugin/Public/PooledProjectileComponent.h"

AWeapon::AWeapon()
{
	ProjectilePool = CreateDefaultSubobject<UPooledProjectileComponent>(TEXT("Pool"));
}

void AWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ProjectilePool)
	{
		
	}
}

void AWeapon::Fire_Implementation()
{

}
