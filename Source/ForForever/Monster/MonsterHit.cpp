// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterHit.h"
#include "../Facilities/BaseFacility.h"
#include "Monster.h"

// Sets default values
AMonsterHit::AMonsterHit() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 碰撞体
	HiterBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HiterBox"));
	RootComponent = HiterBox;
	HiterBox->SetupAttachment(RootComponent);
	HiterBox->SetBoxExtent(FVector(20, 20, 20));
	HiterBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	HiterBox->OnComponentHit.AddDynamic(this, &AMonsterHit::OnHit);

	// 抛射体组件
	ProjectileMovement =
	    CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(HiterBox);
	ProjectileMovement->ProjectileGravityScale = 0.0f; // 关闭重力

	// todo 删除静态网格体对象
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(HiterBox);

	// Script/Engine.StaticMesh'/Game/Monster/Mesh/MonsterHit.MonsterHit'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(
	    TEXT("StaticMesh'/Game/Facilities/Projectile/Shell.Shell'"));
	StaticMesh->SetStaticMesh(StaticMeshAsset.Object); // 设置网格体对象
	SetActorScale3D(FVector(0.1, 0.1, 0.1));

	Damage = 0;
}

// Called when the game starts or when spawned
void AMonsterHit::BeginPlay() { Super::BeginPlay(); }

void AMonsterHit::InitMonsterHit(FVector v, float dmg) {
	ProjectileMovement->Velocity = v;
	Damage = dmg;
}

void AMonsterHit::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                        UPrimitiveComponent *OtherComponent, FVector NormalImpulse,
                        const FHitResult &Hit) {
	// UE_LOG(LogTemp, Warning, TEXT("AMonsterHit::OnHit"));
	if (OtherActor->IsA(AMonster::StaticClass())) return;
	else if (OtherActor->IsA(ABaseFacility::StaticClass()))
		Cast<ABaseFacility>(OtherActor)->OnTakeDamage(this, Damage);

	Destroy();
}

// Called every frame
void AMonsterHit::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
