// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/TimelineComponent.h"
#include "EyeballBoss.generated.h"

UCLASS()
class EYEBALL_BOSSFIGHT_API AEyeballBoss : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* eyeballRoot;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* eyeballMesh;
	
	class UTimelineComponent* timeLine;

public:
	UPROPERTY(EditAnywhere, Category = "Behaviour")
		class UBehaviorTree* behaviorTree;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* FacingDirection;

	UPROPERTY(EditAnywhere, Category = "Timeline")
		class UCurveFloat* bounceCurve;

	UPROPERTY()
		FVector startPos;
	UPROPERTY()
		FVector endPos;

	UPROPERTY(EditAnywhere, Category = "Timeline")
		float zOffset;

	//Delegate to be binded with TimelineFloatReturn()
	FOnTimelineFloat InterpFunction{};

	//Delegate to be binded with TimelineFinished()
	FOnTimelineEvent TimelineFinished{};

public:
	// Sets default values for this pawn's properties
	AEyeballBoss();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void TimelineFloatReturn(float value);
	UFUNCTION()
		void OnTimelineFinished();
};
