// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserBeam.generated.h"

UCLASS()
class EYEBALL_BOSSFIGHT_API ALaserBeam : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* laserRoot;
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* particleSystem;
	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* laserAudio;
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* FireParticleSystem;

private:
	FVector laserStart;
	FVector laserEnd;

public:
	// Sets default values for this actor's properties
	ALaserBeam();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetLaserSource(FVector pos);

	UFUNCTION(BlueprintCallable)
	void SetLaserTarget(FVector pos);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CastRaycast();
};
