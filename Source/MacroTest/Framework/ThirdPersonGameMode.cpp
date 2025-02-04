// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonGameMode.h"
#include "ThirdPersonCharacter.h"
#include "ThirdPersonPC.h"
#include "UObject/ConstructorHelpers.h"

AThirdPersonGameMode::AThirdPersonGameMode()
{
	// Выключаем тик, если он нам не нужен
	PrimaryActorTick.bCanEverTick = false;
	
	// установите класс пешки по умолчанию для нашего персонажа Blueprinted
	// Пример плох тем что расположение блюпринта зашито в исходный код
	/*
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	*/
	
	// Другой пример, подходит если нужен С++ класс, не годиться при наличии блюпринта наследника
	DefaultPawnClass = AThirdPersonCharacter::StaticClass();
	PlayerControllerClass = AThirdPersonPC::StaticClass();
}
