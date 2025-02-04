// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonPC.generated.h"

/**
*  Это класс, который управляет взаимодействием игрока с игрой.
*  Он связывает ввод игрока (клавиатура, мышь, геймпад) с логикой игры.
 */
UCLASS()
class MACROTEST_API AThirdPersonPC : public APlayerController
{
	GENERATED_BODY()

public:
	AThirdPersonPC();

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
