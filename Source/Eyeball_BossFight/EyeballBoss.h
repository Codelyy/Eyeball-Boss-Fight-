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
	
	class UTimelineComponent* bounceTimeLine;
	class UTimelineComponent* eyeColourTimeLine;

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
	FOnTimelineFloat BounceInterpFunction{};
	//Delegate to be binded with TimelineFinished()
	FOnTimelineEvent BounceTimelineFinished{};

	UPROPERTY(EditAnywhere, Category = "Timeline")
	class UCurveFloat* eyeColourCurve;

	//Delegate to be binded with TimelineFloatReturn()
	FOnTimelineFloat EyeColourInterpFunction{};

private:
	FLinearColor eyeColour;

public:
	// Sets default values for this pawn's properties
	AEyeballBoss();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetLookAtPlayer(bool value);

	UFUNCTION(BlueprintCallable)
		void ChangeEyeColour(FLinearColor colour);

	UFUNCTION(BlueprintCallable)
		void SetBounce(bool value);

	UFUNCTION(BlueprintCallable)
		void ResetBouncePosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void BounceTimelineFloatReturn(float value);
	UFUNCTION()
		void BounceOnTimelineFinished();

	UFUNCTION()
		void EyeColourTimelineFloatReturn(float value);
};
