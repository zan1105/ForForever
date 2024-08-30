// Fill out your copyright notice in the Description page of Project Settings.

#include "PShell.h"
#include "../Monster/Monster.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/DamageEvents.h"

// 伤害表
const float APShell::DamageTable[9] = {40.0, 50.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 170.0};

// Sets default values
APShell::APShell() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	ProjectileMovement =
	    CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(RootComponent);
	ProjectileMovement->ProjectileGravityScale = 1.0f; // 关闭重力
	ProjectileMovement->Velocity = FVector(0.0f, 10.0f, -50.0f);

	SetActorScale3D(FVector(0.25, 0.25, 0.25));

	// Script/Engine.StaticMesh'/Game/Facilities/Projectile/Shell.Shell'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(
	    TEXT("StaticMesh'/Game/Facilities/Projectile/Shell.Shell'"));
	StaticMesh->SetStaticMesh(StaticMeshAsset.Object); // 设置网格体对象

	StaticMesh->SetNotifyRigidBodyCollision(true);                // 碰撞后通知
	StaticMesh->SetCollisionProfileName(TEXT("BlockAllDynamic")); // 设置碰撞属性
	StaticMesh->OnComponentHit.AddDynamic(this, &APShell::OnHit); // 绑定碰撞事件
}

// Called when the game starts or when spawned
void APShell::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void APShell::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void APShell::InitShell(uint8 l, FVector v) {
	ShellLevel = l;
	ProjectileMovement->Velocity = v;
}

void APShell::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                    UPrimitiveComponent *OtherComponent, FVector NormalImpulse,
                    const FHitResult &Hit) {
	// UE_LOG(LogTemp, Warning, TEXT("APShell::OnHit"));
	float damage = DamageTable[ShellLevel - 1];
	if (ShellLevel < 3) { // 1 级和 2 级的炮弹，造成单体伤害
		// todo 怪物需要实现 TakeDamage
		if (OtherActor->IsA(AMonster::StaticClass()))
			OtherActor->TakeDamage(damage, FDamageEvent(), nullptr, this);

	} else { // 3 级以上的炮弹，造成范围伤害
		TArray<AActor *> OverlapActors;

		float   Radius = ShellLevel == 9 ? 200.0f : 100.0f;
		FVector Origin = GetActorLocation();
		FVector BoxExtent = FVector(Radius, Radius, Radius);
		UKismetSystemLibrary::BoxOverlapActors(
		    GetWorld(), Origin, BoxExtent,
		    TArray<TEnumAsByte<EObjectTypeQuery>>(), // 对象类型列表（静态或动态，为了性能优化）
		    AMonster::StaticClass(),                 // Actor 类型: 怪物
		    TArray<AActor *>(),                      // 忽略的 Actor 列表
		    OverlapActors);

		for (auto &Actor : OverlapActors) {
			float distance = FVector::Distance(Origin, Actor->GetActorLocation()); // 计算距离
			float damage_tmp = damage * (1 - distance / Radius);                   // 计算伤害
			Actor->TakeDamage(damage_tmp, FDamageEvent(), nullptr, this);          // 造成伤害
		}
	}
	Destroy();
}
