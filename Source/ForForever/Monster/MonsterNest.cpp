// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterNest.h"
#include "Monster.h"

// Sets default values
AMonsterNest::AMonsterNest() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnParams.SpawnCollisionHandlingOverride =
	    ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
}

// Called when the game starts or when spawned
void AMonsterNest::BeginPlay() {
	Super::BeginPlay();

	BirthTime = 0.0f;
	CurrTime = 0.0f;
	ProductTime = 1.0f;
}

// Called every frame
void AMonsterNest::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	BirthTime += DeltaTime;
	CurrTime += DeltaTime;
	if (CurrTime >= ProductTime) {
		CurrTime = 0.0f;
		uint8 monsterLvl;
		if (BirthTime < 120.0f) {
			monsterLvl = 1;
			ProductTime = 1.0f;
		} else if (BirthTime < 240.0f) {
			monsterLvl = 2;
			ProductTime = 0.5f;
		} else {
			monsterLvl = 3;
			ProductTime = 0.1f;
		}
		AMonster *TmpMonster = GetWorld()->SpawnActor<AMonster>(
		    GetActorLocation() + FVector(0, 0, 50), FRotator::ZeroRotator, SpawnParams);
		TmpMonster->InitMonster(monsterLvl);
	}
}
