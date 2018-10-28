// Fill out your copyright notice in the Description page of Project Settings.

#include "EyeballBoss.h"
#include "EyeballBossController.h"
#include "Eyeball_BossFightCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "LookAtPlayer.h"
#include "Components/PointLightComponent.h"
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

	bounceTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("BounceTimeLine"));
	BounceInterpFunction.BindUFunction(this, FName("BounceTimelineFloatReturn"));
	BounceTimelineFinished.BindUFunction(this, FName("BounceOnTimelineFinished"));
	zOffset = 50.0f;

	eyeColourTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EyeColourTimeLine"));
	EyeColourInterpFunction.BindUFunction(this, FName("EyeColourTimelineFloatReturn"));
}

// Called when the game starts or when spawned
void AEyeballBoss::BeginPlay()
{
	Super::BeginPlay();

	AEyeballBossController* AIController = Cast<AEyeballBossController>(GetController());
	AEyeball_BossFightCharacter* player = Cast<AEyeball_BossFightCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (bounceCurve)
	{
		bounceTimeLine->AddInterpFloat(bounceCurve, BounceInterpFunction, FName("Alpha"));
		bounceTimeLine->SetTimelineFinishedFunc(BounceTimelineFinished);

		startPos = GetActorLocation();
		endPos = FVector(startPos.X, startPos.Y, startPos.Z + zOffset);

		//Setting Timeline settings
		bounceTimeLine->SetLooping(false);
		bounceTimeLine->SetIgnoreTimeDilation(true);

		//Start the Timeline
		bounceTimeLine->Play();
	}

	if (eyeColourCurve)
	{
		eyeColourTimeLine->AddInterpFloat(eyeColourCurve, EyeColourInterpFunction, FName("Alpha"));

		eyeColour = FindComponentByClass<UPointLightComponent>()->GetLightColor();

		//Setting Timeline settings
		eyeColourTimeLine->SetLooping(false);
		eyeColourTimeLine->SetIgnoreTimeDilation(true);
	}
}

// Called every frame
void AEyeballBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEyeballBoss::SetLookAtPlayer(bool value)
{
	FindComponentByClass<ULookAtPlayer>()->SetRotate(value);
}

void AEyeballBoss::ChangeEyeColour(FLinearColor colour)
{
	eyeColour = colour;
	eyeColourTimeLine->PlayFromStart();
}

void AEyeballBoss::SetBounce(bool value)
{
	if (value && !bounceTimeLine->IsActive())
	{
		bounceTimeLine->Play();
	}
	else if (!value && bounceTimeLine->IsActive())
	{
		bounceTimeLine->Stop();
	}
}

void AEyeballBoss::BounceTimelineFloatReturn(float value)
{
	SetActorLocation(FMath::Lerp(startPos, endPos, value));
}

void AEyeballBoss::BounceOnTimelineFinished()
{
	if (bounceTimeLine->GetPlaybackPosition() == 0.0f)
	{
		bounceTimeLine->Play();
	}
	else
	{
		bounceTimeLine->Reverse();
	}
}

void AEyeballBoss::EyeColourTimelineFloatReturn(float value)
{
	FLinearColor pointLightColour = FindComponentByClass<UPointLightComponent>()->GetLightColor();
	FLinearColor lerpColour = UKismetMathLibrary::LinearColorLerp(pointLightColour, eyeColour, value);

	FindComponentByClass<UPointLightComponent>()->SetLightColor(lerpColour);
}