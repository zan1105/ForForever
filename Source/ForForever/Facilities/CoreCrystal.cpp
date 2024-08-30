// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreCrystal.h"

/// Script/Engine.SkeletalMesh'/Game/Facilities/Crystal/Crystal_SkelMesh.Crystal_SkelMesh'

// Sets default values
ACoreCrystal::ACoreCrystal() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 设置网格体对象 '/Game/Facilities/Crystal/Crystal_SkelMesh.Crystal_SkelMesh'
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(
	    TEXT("SkeletalMesh'/Game/Facilities/Crystal/Crystal_SkelMesh.Crystal_SkelMesh'"));
	SkeletalMesh->SetSkeletalMesh(SkeletalMeshAsset.Object);

	FacilityType = "CoreCrystal";
	InitFacility();
}

void ACoreCrystal::InitFacility() {
	FacilityLevel = 1;
	Price = 50;
	UpCost = 25;
	Durability = 300;
	Injury = 1.0;
	Period = 4.0;
	AutoRepair = false;
	RepairThreshold = 50;
	RepairValue = 10;
	EnemyNum = 2;
	CollisionBox->SetBoxExtent(FVector(60, 60, 100));
	CollisionBox->SetRelativeLocation(FVector(-9, -9, 100));

	SetActorScale3D(FVector(2.0f, 2.0f, 2.0f));
}
