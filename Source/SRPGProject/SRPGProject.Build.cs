// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SRPGProject : ModuleRules
{
	public SRPGProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

		PrivateDependencyModuleNames.AddRange(new string[] {
			"Slate",
			"SlateCore",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"InputCore",
			"UMG", 
			"GameplayCameras",
			"AIModule",
			"BlueprintGraph"
		});
	}
}
