// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 设置网格体对象 '/Game/Facilities/Projectile/Tower_LVL1.Tower_LVL1'
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(
	    TEXT("SkeletalMesh'/Game/Facilities/Projectile/Tower_LVL1.Tower_LVL1'"));
	if (SkeletalMeshAsset.Succeeded()) {
		SkeletalMesh->SetSkeletalMesh(SkeletalMeshAsset.Object);
		UE_LOG(LogTemp, Warning,
		       TEXT("ZANZAN: Succeeded to load "
		            "SkeletalMesh'/Game/Facilities/Projectile/Tower_LVL1.Tower_LVL1'"));
	} else {
		UE_LOG(LogTemp, Error,
		       TEXT("ZANZAN: Failed to load "
		            "SkeletalMesh'/Game/Facilities/Projectile/Tower_LVL1.Tower_LVL1'"));
	}

	FacilityType = "Projectile";
	InitFacility();
}

void AProjectile::InitFacility() {
	FacilityLevel = 1;
	Price = 50;
	UpCost = 25;
	Durability = 100;
	Attack = 0.5;
	Injury = 1.0;
	Period = 2.0;
	AutoRepair = false;
	RepairThreshold = 50;
	RepairValue = 10;
	EnemyNum = 2;
	CollisionBox->SetBoxExtent(FVector(200, 200, 100));
	HitBox->SetBoxExtent(FVector(50, 50, 50));
	HitBox->SetRelativeLocation(FVector(0, 0, 50));

	SetActorScale3D(FVector(2.0, 2.0, 2.0));
}

void AProjectile::LevelUp() {
	FacilityLevel++;

	if (FacilityLevel <= 3) {
		Attack += 0.25;
		Injury -= 1.0;
		Period -= 0.5;
		RepairValue += 5;
		EnemyNum++;

	} else if (FacilityLevel < 8) {
		UpCost = 50;
		Attack += 0.1;
		Injury -= 0.2;
		Period -= 0.5;
		RepairValue += 2;
		EnemyNum++;
		if (FacilityLevel == 4) SetActorScale3D(FVector(3.0, 3.0, 3.0));

	} else if (FacilityLevel == 8) {
		UpCost = 100;
		Attack += 0.5;
		Injury -= 0.5;
		Period -= 0.5;
		RepairValue += 10;
		EnemyNum++;
		SetActorScale3D(FVector(4.0, 4.0, 4.0));
	}
}
