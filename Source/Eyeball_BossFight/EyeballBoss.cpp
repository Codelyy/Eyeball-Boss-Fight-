// Fill out your copyright notice in the Description page of Project Settings.

#include "EyeballBoss.h"
#include "EyeballBossController.h"
#include "Eyeball_BossFightCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "LaserBeam.h"
#include "Components/ArrowComponent.h"

// Sets default values
AEyeballBoss::AEyeballBoss()
{
	eyeballRoot = CreateDefaultSubobject<USceneComponent>(TEXT("EyeballRoot"));
	RootComponent = eyeballRoot;

	eyeballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EyeballMesh"));
	eyeballMesh->AttachToComponent(eyeballRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	FacingDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("FacingDirection"));
	FacingDirection->AttachToComponent(eyeballRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AEyeballBoss::BeginPlay()
{
	Super::BeginPlay();

	AEyeballBossController* AIController = Cast<AEyeballBossController>(GetController());
	AEyeball_BossFightCharacter* player = Cast<AEyeball_BossFightCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (AIController)
	{
		AIController->SetPlayerToFollow(player);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Failed"));
	}
}

// Called every frame
void AEyeballBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEyeballBoss::ShootLaserBeam()
{
	FActorSpawnParameters spawnInfo;
	GetWorld()->SpawnActor<ALaserBeam>(GetActorLocation(), GetActorRotation(), spawnInfo);
}

