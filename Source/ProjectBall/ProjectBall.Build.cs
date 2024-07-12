// © 2024 Pulse Core Interactive. All rights reserved.

using UnrealBuildTool;

public class ProjectBall : ModuleRules
{
	public ProjectBall(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		OptimizeCode = CodeOptimization.Never;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
			, "CoreUObject"
			, "Engine"
			, "InputCore"
			, "EnhancedInput"
			, "AIModule", "AITestSuite"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "OpenSubdiv" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
