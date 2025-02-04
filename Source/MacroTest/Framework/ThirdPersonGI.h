// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ThirdPersonGI.generated.h"

/**
 *  Это глобальный объект, который существует на протяжении всей игры,
 *  даже при переходе между уровнями. Он используется для хранения данных,
 *  которые должны сохраняться между уровнями или сессиями.
 *  GameInstance — это мощный инструмент для управления глобальными аспектами игры.
 */
UCLASS()
class MACROTEST_API UThirdPersonGI : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;
};
