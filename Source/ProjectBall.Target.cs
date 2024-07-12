// © 2024 Pulse Core Interactive. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectBallTarget : TargetRules
{
	public ProjectBallTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "ProjectBall" } );
	}
}
