// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MobileDiablo : ModuleRules
{
	public MobileDiablo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		OptimizeCode = CodeOptimization.Never;
	
		PublicDependencyModuleNames.AddRange(new string[] { });

		PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "InputCore", "EzAttributes", "ShowEquipment", "UMG", "AIModule", "GameplayTags"});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
