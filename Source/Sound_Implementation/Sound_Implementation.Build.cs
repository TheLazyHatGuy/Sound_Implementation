// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sound_Implementation : ModuleRules
{
	public Sound_Implementation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG"
		});
	}
}
