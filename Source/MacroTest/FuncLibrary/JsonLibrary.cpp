#include "JsonLibrary.h"
#include "JsonObjectConverter.h"
#include "ReadWriteFile.h"

TSharedPtr<FJsonObject> UJsonLibrary::ReadJson(const FString& JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Попытка чтения файла
	const FString JsonString = UReadWriteFile::ReadStringFromFile(JsonFilePath, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return nullptr;
	}

	TSharedPtr<FJsonObject> RetJsonObject;
	
	// Попытка конвертировать в строку
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("JSON Deserialize - FAILED..."));
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read JSON - SUCCESSFUL!!!"));
	return RetJsonObject;
}

void UJsonLibrary::WriteJson(const FString& JsonFilePath, const TSharedPtr<FJsonObject>& JsonObject, bool& bOutSuccess,
	FString& OutInfoMessage)
{
	FString JsonString;

	// Попытка конвертировать в строку
	if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&JsonString)))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("JSON Serialize - FAILED..."));
		return;
	}

	// Попытка записать в файл
	UReadWriteFile::WriteStringToFile(JsonFilePath, JsonString, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Write JSON - SUCCESSFUL!!!"));
}

FJsonTestStruct UJsonLibrary::ReadStructFromJsonFile(const FString JsonFilePath, bool& bOutSuccess,
	FString& OutInfoMessage)
{
	// Попытка прочитать из файла
	const TSharedPtr<FJsonObject> JsonObject = ReadJson(JsonFilePath, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return FJsonTestStruct();
	}

	FJsonTestStruct JsonTestStruct;

	// Попытка конвертировать в структуру
	if (!FJsonObjectConverter::JsonObjectToUStruct<FJsonTestStruct>(JsonObject.ToSharedRef(), &JsonTestStruct))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Convert struct to JSON - FAILED..."));
		return FJsonTestStruct();
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read JSON and convert - SUCCESSFUL!!!"));
	return JsonTestStruct;
	
}

void UJsonLibrary::WriteStructToJsonFile(const FString JsonFilePath, const FJsonTestStruct Struct, bool& bOutSuccess,
	FString& OutInfoMessage)
{
	// Попытка конвертировать структуру в JSON
	const TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Struct);
	if (JsonObject == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write struct to JSON - FAILED..."));
		return;
	}

	// Попытка записать в файл
	WriteJson(JsonFilePath, JsonObject, bOutSuccess, OutInfoMessage);
}
