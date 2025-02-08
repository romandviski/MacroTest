// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteFile.generated.h"

/**
 * Библиотека для работы с файлами на диске
 */
UCLASS()
class MACROTEST_API UReadWriteFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Открывает файл на диске и считывеет из него контент
	 * @param FilePath Путь до файла на диске
	 * @param bOutSuccess Была ли операция успешна
	 * @param OutInfoMessage Больше информации о результатах работы
	 * @return Строка с контентом из файла
	 */
	UFUNCTION(BlueprintCallable, Category = "ReadWriteFile")
	static FString ReadStringFromFile(const FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Создаёт текстовый файл с заданным контентом
	 * @param FilePath Путь до файла на диске
	 * @param String 
	 * @param bOutSuccess Была ли операция успешна
	 * @param OutInfoMessage  Больше информации о результатах работы
	 */
	UFUNCTION(BlueprintCallable, Category = "ReadWriteFile")
	static void WriteStringToFile(const FString FilePath, const FString String, bool& bOutSuccess, FString& OutInfoMessage);
};
