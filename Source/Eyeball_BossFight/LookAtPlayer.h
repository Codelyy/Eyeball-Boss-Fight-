// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LookAtPlayer.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EYEBALL_BOSSFIGHT_API ULookAtPlayer : public UActorComponent
{
	GENERATED_BODY()

private:
	bool rotate;

public:
	UPROPERTY(EditAnywhere, Category = "Behaviour")
		float rotationSpeed;

	// Sets default values for this component's properties
	ULookAtPlayer();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void SetRotate(bool value);
};
