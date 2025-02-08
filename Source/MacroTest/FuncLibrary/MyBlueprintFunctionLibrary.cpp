// © 2024, Mikhail Efremov. All rights reserved.

#include "MyBlueprintFunctionLibrary.h"

FString UMyBlueprintFunctionLibrary::GetAppVersion()
{
	FString AppVersion;
	// Пример чтения из конфига
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		AppVersion,
		GGameIni
	);
	// Пример записи в конфиг
	//GConfig->SetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), TEXT("MySection"), TEXT("MyInfo"), GGameIni);
	return AppVersion;
}