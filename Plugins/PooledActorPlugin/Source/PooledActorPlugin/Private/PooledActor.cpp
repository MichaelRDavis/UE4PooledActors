// Fill out your copyright notice in the Description page of Project Settings.

#include "PooledActor.h"

APooledActor::APooledActor()
{
	bIsActive = true;
	bAutoActivate = false;

	bReplicates = true;
}

void APooledActor::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoActivate)
	{
		ActivateActor();
	}
}

void APooledActor::ActivateActor()
{
	bIsActive = true;
	SetActorTickEnabled(true);
	SetReplicates(true);
}

void APooledActor::DeactivateActor()
{
	bIsActive = false;
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

