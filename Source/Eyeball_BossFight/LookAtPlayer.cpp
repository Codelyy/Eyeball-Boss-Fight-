// Fill out your copyright notice in the Description page of Project Settings.

#include "LookAtPlayer.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
ULookAtPlayer::ULookAtPlayer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void ULookAtPlayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (rotate)
	{
		FVector playerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		FRotator rotationDir = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), playerPos);
		//GetOwner()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), playerPos), ETeleportType::None);
		GetOwner()->SetActorRotation(FMath::RInterpTo(GetOwner()->GetActorRotation(), rotationDir, DeltaTime, rotationSpeed), ETeleportType::None);
	}
}

void ULookAtPlayer::SetRotate(bool value)
{
	rotate = value;
}

