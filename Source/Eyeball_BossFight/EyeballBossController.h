// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EyeballBossController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class EYEBALL_BOSSFIGHT_API AEyeballBossController : public AAIController
{
	GENERATED_BODY()

public:
	AEyeballBossController();

	virtual void Possess(APawn* pawn) override;
	virtual void Tick(float DeltaTime) override;

	void SetPlayerToFollow(APawn* pawn);

	UFUNCTION(BlueprintCallable)
		void LaserBeamState();

protected:
	UBehaviorTreeComponent * behaviorComp;
	UBlackboardComponent* blackboardComp;

};
