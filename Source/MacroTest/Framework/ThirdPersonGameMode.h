// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdPersonGameMode.generated.h"

/**
*  GameMode определяет правила и логику игры.
*  Он управляет основными аспектами игрового процесса, такими как:
*  Как игра начинается.
*  Как игроки появляются на уровне.
*  Какие условия победы или поражения.
*/
UCLASS(minimalapi)
class AThirdPersonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AThirdPersonGameMode();
	
};
