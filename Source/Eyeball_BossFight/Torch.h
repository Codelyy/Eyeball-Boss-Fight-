// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Torch.generated.h"

UCLASS()
class EYEBALL_BOSSFIGHT_API ATorch : public AActor
{
	GENERATED_BODY()
	
	class UTimelineComponent* torchColourTimeline;

public:	

	UPROPERTY(EditAnywhere, Category = "Timeline")
		class UCurveFloat* colourChangeCurve;

	//Delegate to be binded with TimelineFloatReturn()
	FOnTimelineFloat TorchColourInterpFunction{};

private:
	FLinearColor torchColour;

public:
	// Sets default values for this actor's properties
	ATorch();

	UFUNCTION(BlueprintCallable)
		void ChangeTorchColour(FLinearColor colour);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

private:
	UFUNCTION()
		void TorchColourTimelineFloatReturn(float value);
};
