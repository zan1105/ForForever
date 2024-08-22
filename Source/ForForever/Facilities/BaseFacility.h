// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BaseFacility.generated.h"

UCLASS()
class FORFOREVER_API ABaseFacility : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseFacility();

protected:
	virtual void BeginPlay() override;                                       // 构造后调用
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; // 析构前调用

	// 攻击范围碰撞体
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForForever|Facility")
	class UBoxComponent *CollisionBox;

	// 受击碰撞体
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForForever|Facility")
	class UBoxComponent *HitBox;

	// 骨骼网格体对象
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForForever|Facility")
	class USkeletalMeshComponent *SkeletalMesh;

	// 定时器，执行动作周期
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForForever|Facility")
	FTimerHandle PeriodTimer;

	FString FacilityType;    // 设施类型
	uint8   FacilityLevel;   // 设施等级
	uint8   Price;           // 设施建造成本
	uint8   UpCost;          // 设施升级成本
	double  Durability;      // 设施耐久度
	double  Attack;          // 设施攻击力系数
	double  Injury;          // 设施承伤系数
	double  Period;          // 设施动作周期
	bool    AutoRepair;      // 设施自动修复
	double  RepairThreshold; // 设施修复阈值
	double  RepairValue;     // 设施修复量
	uint8   EnemyNum;        // 可攻击设施的敌人数量期望值

	virtual void InitFacility();      // 初始化设施
	virtual void OnPeriodAction();    // 执行周期动作
	virtual void OnFirstAbility() {}  // 释放第一技能，3 级开启
	virtual void OnSecondAbility() {} // 释放第二技能，9 级开启

	void Repair(); // 修复设施

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void LevelUp() {} // 升级设施

	// Getter
	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	FString GetFacilityType() const { return FacilityType; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	uint8 GetFacilityLevel() const { return FacilityLevel; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	uint8 GetPrice() const { return Price; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	uint8 GetUpCost() const { return UpCost; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	double GetDurability() const { return Durability; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	double GetAttack() const { return Attack; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	double GetInjury() const { return Injury; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	double GetPeriod() const { return Period; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	bool GetAutoRepair() const { return AutoRepair; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	double GetRepairThreshold() const { return RepairThreshold; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	double GetRepairValue() const { return RepairValue; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	uint8 GetEnemyNum() const { return EnemyNum; }
};
