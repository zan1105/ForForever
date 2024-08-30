// Fill out your copyright notice in the Description page of Project Settings.

#include "BlockFence.h"

// Sets default values
ABlockFence::ABlockFence() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 设置网格体对象 '/Game/Facilities/BlockFence/Fence.Fence'
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(
	    TEXT("SkeletalMesh'/Game/Facilities/BlockFence/Fence.Fence'"));
	SkeletalMesh->SetSkeletalMesh(SkeletalMeshAsset.Object);

	FacilityType = "BlockFence";
	InitFacility();
}

void ABlockFence::InitFacility() {
	FacilityLevel = 1;
	Price = 50;
	UpCost = 25;
	Durability = 100;
	Injury = 1.0;
	Period = 4.0;
	AutoRepair = false;
	RepairThreshold = 40;
	RepairValue = 30;
	EnemyNum = 5;
	Damage = 0;
	CollisionBox->SetBoxExtent(FVector(400, 80, 200));
	CollisionBox->SetRelativeLocation(FVector(0, 0, 200));

	SetActorScale3D(FVector(0.5, 0.5, 0.5));
}

void ABlockFence::OnPeriodAction() {
	Super::OnPeriodAction();
	// UE_LOG(LogTemp, Warning, TEXT("BlockFence's OnPeriodAction"));
}

void ABlockFence::LevelUp() {
	FacilityLevel++;

	if (FacilityLevel <= 3) {
		Injury -= 0.25;
		Period -= 0.5;
		RepairValue += 5;
		EnemyNum += 3;
		Damage += 5.0;

	} else if (FacilityLevel < 8) {
		UpCost = 50;
		Injury -= 0.05;
		Period -= 0.1;
		RepairValue += 2;
		EnemyNum += 3;
		Damage += 4.0;
		if (FacilityLevel == 4) CollisionBox->SetBoxExtent(FVector(400, 200, 200));

	} else if (FacilityLevel == 8) {
		UpCost = 100;
		Injury -= 0.15;
		Period -= 0.5;
		RepairValue += 10;
		EnemyNum += 3;
		Damage += Damage;
		CollisionBox->SetBoxExtent(FVector(400, 400, 200));
	}
}
