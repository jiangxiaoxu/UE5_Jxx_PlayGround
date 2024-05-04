// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "bbunStyle.h"

class FbbunCommands : public TCommands<FbbunCommands>
{
public:

	FbbunCommands()
		: TCommands<FbbunCommands>(TEXT("bbun"), NSLOCTEXT("Contexts", "bbun", "bbun Plugin"), NAME_None, FbbunStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
