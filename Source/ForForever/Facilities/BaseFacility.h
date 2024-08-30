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
	float   Durability;      // 设施耐久度
	float   Injury;          // 设施承伤系数
	float   Period;          // 设施动作周期
	bool    AutoRepair;      // 设施自动修复
	float   RepairThreshold; // 设施修复阈值
	float   RepairValue;     // 设施修复量
	uint8   EnemyNum;        // 可攻击设施的敌人数量期望值

	virtual void InitFacility();   // 初始化设施
	virtual void OnPeriodAction(); // 执行周期动作

	void Repair(); // 修复设施

public:
	virtual void Tick(float DeltaTime) override; // 每帧调用

	virtual void LevelUp() {} // 升级设施

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	virtual void OnTakeDamage(AActor *Damager, float Damage); // 受到伤害

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
	float GetDurability() const { return Durability; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	float GetInjury() const { return Injury; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	float GetPeriod() const { return Period; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	bool GetAutoRepair() const { return AutoRepair; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	float GetRepairThreshold() const { return RepairThreshold; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	float GetRepairValue() const { return RepairValue; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	uint8 GetEnemyNum() const { return EnemyNum; }
};
