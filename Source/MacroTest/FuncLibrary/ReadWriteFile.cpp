// © 2024, Mikhail Efremov. All rights reserved.

#include "ReadWriteFile.h"

FString UReadWriteFile::ReadStringFromFile(const FString FilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// В сборке игры путь, возвращаемый этим методом, указывает на директорию,
	// вроде C:/Program Files/НазваниеИгры/НазваниеИгры/ИмяФайла
	// Используйте FPaths::ProjectContentDir(), FPaths::ProjectConfigDir()
	// и другие методы для доступа к конкретным папкам (например, Content, Config).
	const FString FullFilePath = FPaths::ProjectDir() + FilePath;
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FullFilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write file - FAILED... File does not exist"));
		return "";
	}

	FString RetReadString = "";

	if (!FFileHelper::LoadFileToString(RetReadString, *FullFilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write file - FAILED... File is not a text file"));
		return "";
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read - SUCCESSFUL!!!"));
	return RetReadString;
}

void UReadWriteFile::WriteStringToFile(const FString FilePath, const FString String, bool& bOutSuccess, FString& OutInfoMessage)
{
	// В сборке игры путь, возвращаемый этим методом, указывает на директорию,
	// вроде C:/Program Files/НазваниеИгры/НазваниеИгры/ИмяФайла
	const FString FullFilePath = FPaths::ProjectDir() + FilePath;
	if (!FFileHelper::SaveStringToFile(String, *FullFilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write file - FAILED..."));
		return;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Write file - SUCCESSFUL!!!"));
}
