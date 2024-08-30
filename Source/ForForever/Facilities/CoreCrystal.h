// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseFacility.h"
#include "CoreCrystal.generated.h"

/**
 *
 */
UCLASS()
class FORFOREVER_API ACoreCrystal : public ABaseFacility {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoreCrystal();

protected:
	virtual void InitFacility() override; // 初始化
	// virtual void OnPeriodAction() override; // 执行周期动作
};
