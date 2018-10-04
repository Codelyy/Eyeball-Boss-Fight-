// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EyeballBoss.generated.h"

UCLASS()
class EYEBALL_BOSSFIGHT_API AEyeballBoss : public APawn
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere)
		class USceneComponent* eyeballRoot;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* eyeballMesh;
	

public:
	UPROPERTY(EditAnywhere, Category = "Behaviour")
		class UBehaviorTree* behaviorTree;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* FacingDirection;

private:
	class ALaserBeam* laserBeam;

public:
	// Sets default values for this pawn's properties
	AEyeballBoss();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShootLaserBeam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
