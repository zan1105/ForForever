// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"
#include "../Facilities/BaseFacility.h"
#include "../Facilities/CoreCrystal.h"
#include "../Facilities/BlockFence.h"
#include "../Facilities/PShell.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "../Facilities/BlockFence.h"
#include "Components/CapsuleComponent.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "MonsterHit.h"

// Sets default values
AMonster::AMonster() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance
	// if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 设置网格体对象 '/Game/Monster/Mesh/Moster.Moster'
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(
	    TEXT("SkeletalMesh'/Game/Monster/Mesh/Moster.Moster'"));
	GetMesh()->SetSkeletalMesh(SkeletalMeshAsset.Object);

	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0)); // 设置旋转
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));  // 设置位置

	MonsterLevel = 1;
	Health = 100.0f;
	Attack = 10.0f;
	IsAttacking = false;
	TargetFacility = nullptr;
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;
}

void AMonster::InitMonster(uint8 Level) {
	MonsterLevel = Level;
	float scale = FMath::Pow(2.0f, Level - 1);
	Health = 100.0f * scale;
	Attack = 10.0f * scale;
	// 设置移动组件的设置最大行走速度
	GetCharacterMovement()->MaxWalkSpeed = 100.0f + 10.0f * scale;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay() {
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &AMonster::OnHit);

	StartAction();
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AMonster::OnAttack, 2.0f, true);
}

void AMonster::OnAttack() {
	if (!IsAttacking) return;
	FVector      Forward = GetActorForwardVector();
	AMonsterHit *Hiter = GetWorld()->SpawnActor<AMonsterHit>(
	    GetActorLocation() + FVector(0, 0, 50) + Forward * 50, FRotator::ZeroRotator);
	Hiter->InitMonsterHit(Forward * 100, Attack);
}

void AMonster::StartAction() {
	if (!TryNavToTarget(FVector(0, 0, 100))) { // 尝试去攻击 CoreCrystal
		UE_LOG(LogTemp, Warning, TEXT("can't to CoreCrystal"));
		TArray<AActor *> Fences;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlockFence::StaticClass(), Fences);
		Fences.Sort([this](const AActor &A, const AActor &B) { // 按距离排序
			return FVector::Distance(GetActorLocation(), A.GetActorLocation()) <
			       FVector::Distance(GetActorLocation(), B.GetActorLocation());
		});
		for (auto &Fence : Fences) { // 优先去攻击可以到达的最近的 BlockFence
			if (TryNavToTarget(Fence->GetActorLocation())) {
				TargetFacility = Cast<ABlockFence>(Fence);
				break;
			}
		}
	} else {
		TargetFacility = Cast<ABaseFacility>(
		    UGameplayStatics::GetActorOfClass(GetWorld(), ACoreCrystal::StaticClass()));
	}
}

void AMonster::OnTakeDamage(AActor *Damager, float Damage) {
	Health -= Damage;
	if (Health <= 0) {
		if (Damager->IsA(APShell::StaticClass())) {
			APShell *Shell = Cast<APShell>(Damager);
			if (Shell->GetShellLevel() == 9) {
				TArray<AActor *> OverlapActors;
				float            Radius = 100.0f;
				FVector          Origin = GetActorLocation();
				FVector          BoxExtent = FVector(Radius, Radius, Radius);
				UKismetSystemLibrary::BoxOverlapActors(
				    GetWorld(), Origin, BoxExtent,
				    TArray<TEnumAsByte<
				        EObjectTypeQuery>>(), // 对象类型列表（静态或动态，为了性能优化）
				    AMonster::StaticClass(), // Actor 类型: 怪物
				    TArray<AActor *>(),      // 忽略的 Actor 列表
				    OverlapActors);

				for (auto &Actor2 : OverlapActors) {
					float d = FVector::Distance(Origin, Actor2->GetActorLocation()); // 计算距离
					float dt = Damage * (1 - d / Radius);                            // 计算伤害
					Cast<AMonster>(Actor2)->OnTakeDamage(this, dt);                  // 造成伤害
				}
			}
		} else if (Damager->IsA(ABlockFence::StaticClass())) {
			ABlockFence *Fence = Cast<ABlockFence>(Damager);
			if (Fence->GetFacilityLevel() == 9) {
				// todo 眩晕 1 秒
			}
		}
		// todo 增加资金
		Destroy();
	}
}

void AMonster::OnHit(AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse,
                     const FHitResult &Hit) {
	// UE_LOG(LogTemp, Warning, TEXT("AMonster::OnHit"));
	if (OtherActor->IsA(ABaseFacility::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("AMonster::OnHit ABaseFacility"));
		if (!IsAttacking) {
			AAIController *AIController = Cast<AAIController>(GetController());
			if (AIController) AIController->StopMovement(); // 停止 AI 移动
			IsAttacking = true;                             // 开始攻击
		}
	}
}

bool AMonster::TryNavToTarget(FVector Target) {
	UNavigationSystemV1 *NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys) return false;
	FNavLocation Result;

	bool bSuccess = NavSys->GetRandomReachablePointInRadius(Target, 100.0f, Result);
	if (bSuccess) {
		AAIController *AIController = Cast<AAIController>(GetController());
		if (AIController) {
			AIController->MoveToLocation(Target, 200.0f, false);
		}
	}
	return bSuccess;
}

// Called every frame
void AMonster::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (!IsValid(TargetFacility) &&
	    (IsAttacking || !(GetCharacterMovement()->IsMovingOnGround()))) {
		IsAttacking = false;
		StartAction();
	}
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
