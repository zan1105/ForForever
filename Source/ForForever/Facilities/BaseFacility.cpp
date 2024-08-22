// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseFacility.h"

// Sets default values
ABaseFacility::ABaseFacility() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 骨骼网格体对象
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;
	// SkeletalMesh->SetupAttachment(RootComponent);

	// 碰撞体
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);

	FacilityType = "BaseFacility";
	InitFacility();
}

void ABaseFacility::InitFacility() {
	FacilityLevel = 1;
	Price = 50;
	UpCost = 25;
	Durability = 100;
	Attack = 0.5;
	Injury = 4.0;
	Period = 4.0;
	AutoRepair = false;
	RepairThreshold = 50;
	RepairValue = 10;
	EnemyNum = 2;
	CollisionBox->SetBoxExtent(FVector(100, 100, 100));
	HitBox->SetBoxExtent(FVector(50, 50, 50));
	HitBox->SetRelativeLocation(FVector(0, 0, 50));
}

void ABaseFacility::OnPeriodAction() {
	if (AutoRepair && Durability < RepairThreshold) Repair();
}

void ABaseFacility::Repair() {
	Durability += RepairValue;
	// todo 减少资金
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
