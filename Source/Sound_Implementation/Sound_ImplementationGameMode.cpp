// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sound_ImplementationGameMode.h"
#include "Sound_ImplementationHUD.h"
#include "Sound_ImplementationCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASound_ImplementationGameMode::ASound_ImplementationGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASound_ImplementationHUD::StaticClass();
}
