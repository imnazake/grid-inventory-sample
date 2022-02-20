// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GridInventory : ModuleRules
{
	public GridInventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Slate", "SlateCore", "UMG" });
	}
}
