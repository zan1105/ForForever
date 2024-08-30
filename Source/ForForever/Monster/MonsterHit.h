// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MonsterHit.generated.h"

UCLASS()
class FORFOREVER_API AMonsterHit : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMonsterHit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float Damage;

	// 静态网格体对象
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForForever|Facility")
	class UStaticMeshComponent *StaticMesh;

	// 攻击范围碰撞体
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForForever|Monster")
	class UBoxComponent *HiterBox;

	// 抛射体组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForForever|Monster")
	class UProjectileMovementComponent *ProjectileMovement;

	UFUNCTION(BlueprintCallable, Category = "ForForever|Monster")
	void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
	           UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitMonsterHit(FVector v, float dmg);
};
