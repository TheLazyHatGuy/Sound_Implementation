// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Sound_ImplementationHUD.generated.h"

UCLASS()
class ASound_ImplementationHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASound_ImplementationHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

