// Fill out your copyright notice in the Description page of Project Settings.

#include "PooledActor.h"
#include "PooledActorComponent.h"

APooledActor::APooledActor()
{
	bIsActive = false;
	bAutoActivate = false;
	bIsOrphaned = false;

	bReplicates = false;
	bNetUseOwnerRelevancy = false;
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void APooledActor::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoActivate)
	{
		ActivateActor();
	}
}

void APooledActor::Destroyed()
{
	ReturnToOwningPool();
}

void APooledActor::SetLifeSpan(float InLifespan)
{
	PooledActorLifespan = InLifespan;
	GetWorldTimerManager().SetTimer(LifespanHandle, this, &APooledActor::DeactivateActor, PooledActorLifespan, false);
}

void APooledActor::ActivateActor()
{
	bIsActive = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
	SetReplicates(true);
}

void APooledActor::DeactivateActor()
{
	bIsActive = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	SetReplicates(false);
}

void APooledActor::SetIsActive(bool bNewActive)
{
	bIsActive = bNewActive;
}

void APooledActor::SetAutoActivate(bool bNewAutoActivate)
{
	bAutoActivate = bNewAutoActivate;
}

bool APooledActor::IsActive() const
{
	return bIsActive;
}

void APooledActor::ReturnToOwningPool()
{
	if (OwningPool)
	{
		
	}

	// If it's owning pool is destroyed then this pooled actor is now orphaned
	bIsOrphaned = true;
}

void APooledActor::SetOwningPool(UPooledActorComponent* NewOnwer)
{
	OwningPool = NewOnwer;
}

