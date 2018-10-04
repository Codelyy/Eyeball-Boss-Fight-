// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Eyeball_BossFightTarget : TargetRules
{
	public Eyeball_BossFightTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("Eyeball_BossFight");
	}
}
