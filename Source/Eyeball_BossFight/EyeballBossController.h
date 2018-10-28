// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EyeballBossController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class AEyeballBoss;

UCLASS()
class EYEBALL_BOSSFIGHT_API AEyeballBossController : public AAIController
{
	GENERATED_BODY()

public:
	AEyeballBossController();

	virtual void Possess(APawn* pawn) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetState(int state);

	UFUNCTION(BlueprintCallable)
		void SetStateInstant(int state);

protected:
	UBehaviorTreeComponent * behaviorComp;
	UBlackboardComponent* blackboardComp;

private:
	AEyeballBoss* eyeball;

};
