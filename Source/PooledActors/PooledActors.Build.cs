// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PooledActors : ModuleRules
{
	public PooledActors(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine",
			"InputCore", 
			"PooledActorPlugin"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
