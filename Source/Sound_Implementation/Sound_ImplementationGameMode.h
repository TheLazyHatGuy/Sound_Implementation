// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Sound_ImplementationGameMode.generated.h"

UCLASS(minimalapi)
class ASound_ImplementationGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASound_ImplementationGameMode();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString UI_Prompt;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bShowPrompt;
};



