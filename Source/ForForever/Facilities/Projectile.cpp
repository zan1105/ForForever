// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "PShell.h"

// Sets default values
AProjectile::AProjectile() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 设置网格体对象 '/Game/Facilities/Projectile/Tower_LVL1.Tower_LVL1'
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Finder(
	    TEXT("SkeletalMesh'/Game/Facilities/Projectile/Tower_LVL1.Tower_LVL1'"));
	SkeletalMesh->SetSkeletalMesh(Finder.Object);

	FacilityType = "Projectile";
	InitFacility();
}

void AProjectile::InitFacility() {
	FacilityLevel = 1;
	Price = 50;
	UpCost = 25;
	Durability = 100;
	Injury = 1.0;
	Period = 2.0;
	AutoRepair = false;
	RepairThreshold = 50;
	RepairValue = 10;
	EnemyNum = 2;
	CollisionBox->SetBoxExtent(FVector(800, 800, 400));

	SetActorScale3D(FVector(0.5, 0.5, 0.5));
}

void AProjectile::OnPeriodAction() {
	Super::OnPeriodAction();

	// 创建炮弹 Y轴速度范围：100~300
	FVector  v = FVector(0.0f, 300.0f, 500.0f); // todo 根据敌人位置计算速度
	APShell *Shell = GetWorld()->SpawnActor<APShell>(GetActorLocation() + FVector(0, 0, 1000),
	                                                 FRotator::ZeroRotator);
	Shell->InitShell(FacilityLevel, v);
}

void AProjectile::LevelUp() {
	FacilityLevel++;

	if (FacilityLevel <= 3) {
		Injury -= 1.0;
		Period -= 0.5;
		RepairValue += 5;
		EnemyNum++;

	} else if (FacilityLevel < 8) {
		UpCost = 50;
		Injury -= 0.2;
		Period -= 0.5;
		RepairValue += 2;
		EnemyNum++;
		if (FacilityLevel == 4) {
			CollisionBox->SetBoxExtent(FVector(1000, 1000, 400));
			static ConstructorHelpers::FObjectFinder<USkeletalMesh> Finder(
			    TEXT("SkeletalMesh'/Game/Facilities/Projectile/Tower_LVL2.Tower_LVL2'"));
			SkeletalMesh->SetSkeletalMesh(Finder.Object);
		}

	} else if (FacilityLevel == 8) {
		UpCost = 100;
		Injury -= 0.5;
		Period -= 0.5;
		RepairValue += 10;
		EnemyNum++;
		CollisionBox->SetBoxExtent(FVector(1200, 1200, 400));
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> Finder(
		    TEXT("SkeletalMesh'/Game/Facilities/Projectile/Tower_LVL3.Tower_LVL3'"));
		SkeletalMesh->SetSkeletalMesh(Finder.Object);
	}
}
