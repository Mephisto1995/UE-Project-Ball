// © 2024 Pulse Core Interactive. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectBallEditorTarget : TargetRules
{
	public ProjectBallEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "ProjectBall" } );
	}
}
