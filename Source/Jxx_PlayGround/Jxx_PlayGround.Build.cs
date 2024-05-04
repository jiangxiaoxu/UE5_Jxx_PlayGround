// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Jxx_PlayGround : ModuleRules
{
	public Jxx_PlayGround(ReadOnlyTargetRules Target) : base(Target)
	{

		OptimizeCode = CodeOptimization.InShippingBuildsOnly;

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
