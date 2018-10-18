// Fill out your copyright notice in the Description page of Project Settings.

#include "EyeballBoss.h"
#include "EyeballBossController.h"
#include "Eyeball_BossFightCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Components/ArrowComponent.h"

// Sets default values
AEyeballBoss::AEyeballBoss()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	eyeballRoot = CreateDefaultSubobject<USceneComponent>(TEXT("EyeballRoot"));
	RootComponent = eyeballRoot;

	eyeballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EyeballMesh"));
	eyeballMesh->AttachToComponent(eyeballRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	FacingDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("FacingDirection"));
	FacingDirection->AttachToComponent(eyeballRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	timeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));
	zOffset = 50.0f;
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

	if (bounceCurve)
	{
		timeLine->AddInterpFloat(bounceCurve, InterpFunction, FName("Alpha"));
		timeLine->SetTimelineFinishedFunc(TimelineFinished);

		startPos = GetActorLocation();
		endPos = FVector(startPos.X, startPos.Y, startPos.Z + zOffset);

		//Setting Timeline settings
		timeLine->SetLooping(false);
		timeLine->SetIgnoreTimeDilation(true);

		//Start the Timeline
		timeLine->Play();
	}
}

// Called every frame
void AEyeballBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}


void AEyeballBoss::TimelineFloatReturn(float value)
{
	SetActorLocation(FMath::Lerp(startPos, endPos, value));
}

void AEyeballBoss::OnTimelineFinished()
{
	if (timeLine->GetPlaybackPosition() == 0.0f)
	{
		timeLine->Play();
	}
	else
	{
		timeLine->Reverse();
	}
}