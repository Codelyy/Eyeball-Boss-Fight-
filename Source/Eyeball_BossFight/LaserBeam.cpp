// Fill out your copyright notice in the Description page of Project Settings.

#include "LaserBeam.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "EyeballBoss.h"

// Sets default values
ALaserBeam::ALaserBeam()
{
	laserRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Laser Root"));
	RootComponent = laserRoot;

	particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser Beam"));
	particleSystem->AttachToComponent(laserRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	laserAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Laser Audio"));
	laserAudio->AttachToComponent(laserRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	FireParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire"));
	FireParticleSystem->AttachToComponent(laserRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALaserBeam::BeginPlay()
{
	Super::BeginPlay();
}

void ALaserBeam::CastRaycast()
{
	FHitResult* hit = new FHitResult();
	FVector startTrace = laserStart;
	FVector forwardVector = Cast<AEyeballBoss>(GetAttachParentActor())->FacingDirection->GetForwardVector();
	FVector endTrace = ((forwardVector * 5000.0f) + startTrace);
	FCollisionQueryParams* traceParms = new FCollisionQueryParams();

	GetWorld()->LineTraceSingleByChannel(*hit, startTrace, endTrace, ECC_Visibility, *traceParms);

	if (hit)
	{
		FireParticleSystem->Activate();
		FireParticleSystem->SetWorldLocation(hit->Location);
	}
	else
	{
		FireParticleSystem->Deactivate();
	}

	SetLaserSource(startTrace);
	SetLaserTarget(hit->Location);
}

// Called every frame
void ALaserBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector playerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	laserStart = GetActorLocation();
	laserEnd = playerPos;

	CastRaycast();
}

void ALaserBeam::SetLaserSource(FVector pos)
{
	particleSystem->SetBeamSourcePoint(0, pos, 0);
}

void ALaserBeam::SetLaserTarget(FVector pos)
{
	particleSystem->SetBeamTargetPoint(0, pos, 0);
}

