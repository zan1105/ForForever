// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseFacility.h"
#include "BlockFence.generated.h"

/**
 *
 */
UCLASS()
class FORFOREVER_API ABlockFence : public ABaseFacility {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlockFence();

protected:
	double Damage; // 伤害

	virtual void InitFacility() override; // 初始化

public:
	virtual void LevelUp() override; // 升级

	// Getter
	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	double GetDamage() const { return Damage; }
};
