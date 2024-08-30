// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterNest.generated.h"

UCLASS()
class FORFOREVER_API AMonsterNest : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMonsterNest();
	float BirthTime;
	float ProductTime;
	float CurrTime;

	FActorSpawnParameters SpawnParams;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
