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
	if (SkeletalMeshAsset.Succeeded()) {
		SkeletalMesh->SetSkeletalMesh(SkeletalMeshAsset.Object);
		UE_LOG(LogTemp, Warning,
		       TEXT("ZANZAN: Succeeded to load "
		            "SkeletalMesh'/Game/Facilities/BlockFence/Fence.Fence'"));
	} else {
		UE_LOG(LogTemp, Error,
		       TEXT("ZANZAN: Failed to load "
		            "SkeletalMesh'/Game/Facilities/BlockFence/Fence.Fence'"));
	}

	FacilityType = "BlockFence";
	InitFacility();
}

void ABlockFence::InitFacility() {
	FacilityLevel = 1;
	Price = 50;
	UpCost = 25;
	Durability = 100;
	Attack = 0.5;
	Injury = 1.0;
	Period = 4.0;
	AutoRepair = false;
	RepairThreshold = 40;
	RepairValue = 30;
	EnemyNum = 5;
	Damage = 0;
	CollisionBox->SetBoxExtent(FVector(400, 80, 200));
	CollisionBox->SetRelativeLocation(FVector(0, 0, 200));
	HitBox->SetBoxExtent(FVector(400, 100, 200));
	HitBox->SetRelativeLocation(FVector(0, 0, 200));

	SetActorScale3D(FVector(0.5, 0.5, 0.5));
}

void ABlockFence::LevelUp() {
	FacilityLevel++;

	if (FacilityLevel <= 3) {
		Attack += 0.25;
		Injury -= 0.25;
		Period -= 0.5;
		RepairValue += 5;
		EnemyNum += 3;
		Damage += 5.0;

	} else if (FacilityLevel < 8) {
		UpCost = 50;
		Attack += 0.1;
		Injury -= 0.05;
		Period -= 0.5;
		RepairValue += 2;
		EnemyNum += 3;
		Damage += 4.0;
		if (FacilityLevel == 4) CollisionBox->SetBoxExtent(FVector(400, 200, 200));

	} else if (FacilityLevel == 8) {
		UpCost = 100;
		Attack += 0.5;
		Injury -= 0.15;
		Period -= 0.5;
		RepairValue += 10;
		EnemyNum += 3;
		Damage += Damage;
		CollisionBox->SetBoxExtent(FVector(400, 400, 200));
	}
}
