// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonLibrary.generated.h"

class FJsonObject;

USTRUCT(BlueprintType, Category = "JSON")
struct FJsonTestStruct : public FTableRowBase // Таблица не обязательно
{
	GENERATED_BODY()

	// Эти переменные видны как в Blueprint, так и в Json
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " ... ")
	FString MyString = "String value";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " ... ")
	bool MyBool = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " ... ")
	float MyFloat = 123.456f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " ... ")
	int MyInt = 123;

	// Эти переменные не видны в Blueprint, но все равно видны в Json
public:
	UPROPERTY()
	FVector MyVector = { 1.0f, 2.0f, 3.0f };
	UPROPERTY()
	FRotator MyRotator = { 90.0f, 180.0f, 270.0f };
	UPROPERTY()
	FTransform MyTransform;

	// Этой переменной не будет в json, потому что она не отмечена как UPROPERTY()
public:
	FString MyOtherString = "Эта переменная не будет присутствовать в json";
};

/**
 *  Библиотека для работы с JSON файлами
 *  по мотивам видео https://youtu.be/4wJ45mrzrkM
 */
UCLASS()
class MACROTEST_API UJsonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	// Функции доступные в любом блюпринте или CPP файне после инклюда

	/**
	 * Открывает JSON файл, считывает его и конвертирует в FJsonObject
	 * @param JsonFilePath Путь до JSON файла
	 * @param bOutSuccess Была ли операция успешна
	 * @param OutInfoMessage Больше информации о результатах работы
	 * @return FJsonObject с содержимым файла
	 */
	static TSharedPtr<FJsonObject> ReadJson(const FString& JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
	/**
	 * 
	 * @param JsonFilePath Путь до JSON файла
	 * @param JsonObject FJsonObject для записи в файл
	 * @param bOutSuccess Была ли операция успешна
	 * @param OutInfoMessage Больше информации о результатах работы
	 */
	static void WriteJson(const FString& JsonFilePath, const TSharedPtr<FJsonObject>& JsonObject, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Открывает JSON файл, считывает и заполняет структуру
	 * @param JsonFilePath Путь до JSON файла
	 * @param bOutSuccess Была ли операция успешна
	 * @param OutInfoMessage Больше информации о результатах работы
	 * @return Структуру с содержимым JSON
	 */
	UFUNCTION(BlueprintCallable, Category = "JSON")
	static FJsonTestStruct ReadStructFromJsonFile(const FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
	/**
	 * Конвертирует структуру в строку и записывает в файл
	 * @param JsonFilePath Путь до JSON файла
	 * @param Struct Структура для записи в JSON файл
	 * @param bOutSuccess Была ли операция успешна
	 * @param OutInfoMessage Больше информации о результатах работы
	 */
	UFUNCTION(BlueprintCallable, Category = "JSON")
	static void WriteStructToJsonFile(FString JsonFilePath, FJsonTestStruct Struct, bool& bOutSuccess, FString& OutInfoMessage);
};
