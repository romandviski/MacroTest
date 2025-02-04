// © 2024, Mikhail Efremov. All rights reserved.

#include "ThirdPersonGI.h"
#include "GameFramework/GameUserSettings.h"

void UThirdPersonGI::Init()
{
	Super::Init();

	if (GEngine)
	{
		// Меняем пользовательские настройки
		GEngine->GameUserSettings->SetVSyncEnabled(true);
		GEngine->GameUserSettings->ApplySettings(true);
		GEngine->GameUserSettings->SaveSettings();
		// Ограничиваем количество кадров через консольную команду
		GEngine->Exec(GetWorld(), TEXT("t.MaxFPS 60"));
	}
}
