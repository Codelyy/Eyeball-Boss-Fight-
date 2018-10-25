// Fill out your copyright notice in the Description page of Project Settings.

#include "EyeballBossController.h"
#include "Engine.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EyeballBoss.h"

AEyeballBossController::AEyeballBossController()
{
	behaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorComp"));
	blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackboardComp"));
}

void AEyeballBossController::Possess(APawn* pawn)
{
	Super::Possess(pawn);
	UE_LOG(LogTemp, Error, TEXT("Tick!"));

	AEyeballBoss* eyeball = Cast<AEyeballBoss>(pawn);
	if (eyeball)
	{
		if (eyeball->behaviorTree->BlackboardAsset)
		{
			blackboardComp->InitializeBlackboard(*(eyeball->behaviorTree->BlackboardAsset));
			behaviorComp->StartTree(*eyeball->behaviorTree);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Blackboard Asset doesn't exist"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed Cast to Eyeball"));
	}
}

void AEyeballBossController::Tick(float DeltaTime)
{
	blackboardComp->SetValueAsVector(FName("PlayerPosition"), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, blackboardComp->GetValueAsVector(FName("PlayerPosition")).ToString());
}

void AEyeballBossController::SetPlayerToFollow(APawn* pawn)
{
	if (blackboardComp)
	{
		blackboardComp->SetValueAsVector(FName("PlayerToFollow"), pawn->GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Blackboard Component not found"));
	}

}

void AEyeballBossController::LaserBeamState()
{
	blackboardComp->SetValueAsBool(FName("FiringLaser"), true);
}

void AEyeballBossController::SetState(int state)
{
	blackboardComp->SetValueAsEnum(FName("State"), state);
}
