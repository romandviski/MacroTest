// © 2024, Mikhail Efremov. All rights reserved.

#include "ThirdPersonPC.h"

AThirdPersonPC::AThirdPersonPC()
{
	// В контроллере тик нам нужен =)
	PrimaryActorTick.bCanEverTick = true;
}

// Вселение контроллера в пешку
void AThirdPersonPC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Устанавливаем режим ввода в игру при вселении в пешку
	const FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
