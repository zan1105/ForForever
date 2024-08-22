// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseFacility.h"
#include "Projectile.generated.h"

/**
 *
 */
UCLASS()
class FORFOREVER_API AProjectile : public ABaseFacility {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	virtual void InitFacility() override; // 初始化

public:
	virtual void LevelUp() override; // 升级
};
