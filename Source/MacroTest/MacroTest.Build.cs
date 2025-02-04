// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MacroTest : ModuleRules
{
	public MacroTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"
		});
		
		// Чиним инклюды из подпапок проекта
		PublicIncludePaths.AddRange(new string[]
		{
			"MacroTest"
		});

	}
}
