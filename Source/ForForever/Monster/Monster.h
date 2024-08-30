// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Facilities/BaseFacility.h"
#include "Monster.generated.h"

UCLASS()
class FORFOREVER_API AMonster : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "ForForever|Monster")
	virtual void OnHit(AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse,
	                   const FHitResult &Hit);

	// 定时器，执行动作周期
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForForever|Monster")
	FTimerHandle AttackTimer;

	float          Health;
	float          Attack;
	float          AttackSpeed;
	bool           IsAttacking;
	uint8          MonsterLevel;
	ABaseFacility *TargetFacility;

	bool TryNavToTarget(FVector Target); // 尝试导航到目标
	void OnAttack();                     // 攻击

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "ForForever|Monster")
	virtual void OnTakeDamage(AActor *Damager, float Damage);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "ForForever|Monster")
	void InitMonster(uint8 Level);

	void StartAction();

	// Getter
	UFUNCTION(BlueprintCallable, Category = "ForForever|Monster")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Monster")
	uint8 GetMonsterLevel() const { return MonsterLevel; }

	UFUNCTION(BlueprintCallable, Category = "ForForever|Monster")
	bool GetIsAttacking() const { return IsAttacking; }
};
