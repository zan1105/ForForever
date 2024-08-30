// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PShell.generated.h"

UCLASS()
class FORFOREVER_API APShell : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APShell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 静态网格体对象
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForForever|Facility")
	class UStaticMeshComponent *StaticMesh;

	// 抛射体组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForForever|Facility")
	class UProjectileMovementComponent *ProjectileMovement;

	static const float DamageTable[9]; // 伤害表

	uint8 ShellLevel; // 等级

	UFUNCTION(BlueprintCallable, Category = "ForForever|Facility")
	void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
	           UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitShell(uint8 l, FVector v);

	// Getter
	uint8 GetShellLevel() const { return ShellLevel; }
};
