// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gauntlet2 : ModuleRules
{
	public Gauntlet2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Gauntlet2",
			"Gauntlet2/Variant_Platforming",
			"Gauntlet2/Variant_Platforming/Animation",
			"Gauntlet2/Variant_Combat",
			"Gauntlet2/Variant_Combat/AI",
			"Gauntlet2/Variant_Combat/Animation",
			"Gauntlet2/Variant_Combat/Gameplay",
			"Gauntlet2/Variant_Combat/Interfaces",
			"Gauntlet2/Variant_Combat/UI",
			"Gauntlet2/Variant_SideScrolling",
			"Gauntlet2/Variant_SideScrolling/AI",
			"Gauntlet2/Variant_SideScrolling/Gameplay",
			"Gauntlet2/Variant_SideScrolling/Interfaces",
			"Gauntlet2/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
