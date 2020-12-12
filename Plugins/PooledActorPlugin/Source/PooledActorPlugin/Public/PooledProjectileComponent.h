// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledProjectileComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POOLEDACTORPLUGIN_API UPooledProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPooledProjectileComponent();

protected:
	
};
