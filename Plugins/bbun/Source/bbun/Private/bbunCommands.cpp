// Copyright Epic Games, Inc. All Rights Reserved.

#include "bbunCommands.h"

#define LOCTEXT_NAMESPACE "FbbunModule"

void FbbunCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "bbun", "Execute bbun action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
