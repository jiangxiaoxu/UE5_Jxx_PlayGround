// Copyright Epic Games, Inc. All Rights Reserved.

#include "Jxx_PlayGroundGameMode.h"
#include "Jxx_PlayGroundCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJxx_PlayGroundGameMode::AJxx_PlayGroundGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
