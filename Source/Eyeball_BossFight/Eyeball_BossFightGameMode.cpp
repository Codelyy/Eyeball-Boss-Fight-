// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Eyeball_BossFightGameMode.h"
#include "Eyeball_BossFightHUD.h"
#include "Eyeball_BossFightCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEyeball_BossFightGameMode::AEyeball_BossFightGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AEyeball_BossFightHUD::StaticClass();
}
