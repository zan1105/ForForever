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
	float Damage; // 伤害

	virtual void InitFacility() override;   // 初始化
	virtual void OnPeriodAction() override; // 执行周期动作

public:
	virtual void LevelUp() override; // 升级

	// Getter
	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	float GetDamage() const { return Damage; }
};
