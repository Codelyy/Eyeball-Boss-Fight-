// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Eyeball_BossFightHUD.generated.h"

UCLASS()
class AEyeball_BossFightHUD : public AHUD
{
	GENERATED_BODY()

public:
	AEyeball_BossFightHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

