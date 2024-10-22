// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseFacility.h"
#include "../Monster/MonsterHit.h"

// Sets default values
ABaseFacility::ABaseFacility() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 骨骼网格体对象
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;
	// 设置骨骼网格体的碰撞为BlockAllDynamic
	SkeletalMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	// 碰撞体
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);

	FacilityType = "BaseFacility";
	InitFacility();
}

void ABaseFacility::InitFacility() {
	FacilityLevel = 1;
	Price = 50;
	UpCost = 25;
	Durability = 100;
	Injury = 4.0;
	Period = 4.0;
	AutoRepair = false;
	RepairThreshold = 50;
	RepairValue = 10;
	EnemyNum = 2;
	CollisionBox->SetBoxExtent(FVector(100, 100, 100));
}

void ABaseFacility::OnPeriodAction() {
	if (AutoRepair && Durability < RepairThreshold) Repair();
}

void ABaseFacility::Repair() {
	Durability += RepairValue;
	// todo 减少资金
}

void ABaseFacility::OnTakeDamage(AActor *Damager, float Damage) {
	UE_LOG(LogTemp, Warning, TEXT("ABaseFacility::OnTakeDamage"));
	if (Damager->IsA(AMonsterHit::StaticClass())) {
		Durability -= Damage * Injury;
		if (Durability <= 0) Destroy();
	}
}

// Called when the game starts or when spawned
void ABaseFacility::BeginPlay() {
	Super::BeginPlay();

	// 设置定时器
	GetWorldTimerManager().SetTimer(PeriodTimer, this, &ABaseFacility::OnPeriodAction, Period,
	                                true);
}

void ABaseFacility::EndPlay(const EEndPlayReason::Type EndPlayReason) {

	// 清除资源
	GetWorldTimerManager().ClearTimer(PeriodTimer); // 清除定时器
	CollisionBox->DestroyComponent();               // 销毁碰撞体
	SkeletalMesh->DestroyComponent();               // 销毁骨骼网格体对象

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ABaseFacility::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
