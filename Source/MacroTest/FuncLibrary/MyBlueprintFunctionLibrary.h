// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

// описываем собственный енумератор,
// будет доступен везде где мы заинклюдим этот BlueprintFunctionLibrary
UENUM(BlueprintType)
enum class EMyEnumerator : uint8 // название начинается с E, потому что это энумератор
{
	v1 UMETA(DisplayName = "var1"),
	v2 UMETA(DisplayName = "var2"),
	v3 UMETA(DisplayName = "var3"),
};

// Своя структура, пример настроек для пули (проджектаил)
USTRUCT(BlueprintType)
struct FProjectileInfo // название начинается с F, потому что это структура
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ToolTip = "Стартовая скорость пули"))
	float InitialSpeed = 3000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ToolTip = "Время жизни пули"))
	float LifeSpan = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual", meta = (ToolTip = "Моделька пули"))
	UStaticMesh* ProjectileStaticMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual", meta = (ToolTip = "Эффект на пуле"))
	UParticleSystem* ProjectileTrailFx = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect ", meta = (ToolTip = "Звук попадания пули в стену или пол"))
	USoundBase* HitSound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect ", meta = (ToolTip = "Отметина на стене"))
	UMaterialInterface* DecalOnHit = nullptr;
};

// Своя структура для создания на её основе таблицы с настройками оружия
USTRUCT(BlueprintType)
struct FWeaponSetting : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ToolTip = "Множитель меткости"))
	float AccuracyMultiplier = 1.0f;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ToolTip = "Используется ли обойма?"))
	bool bHasClip = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ToolTip = "Размер обоймы", EditCondition = "bHasClip == true", EditConditionHides))
	int32 ClipSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX", meta = (ToolTip = "Эффект из ствола при выстреле"))
	UParticleSystem* EffectFireWeapon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX", meta = (ToolTip = "Звук выстрела"))
	USoundBase* SoundFireWeapon = nullptr;

	// Структура внутри структуры
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings", meta = (ToolTip = "Настройки пули"))
	FProjectileInfo ProjectileInfo;
};

/**
 * Базовый класс для создания библиотек функций, которые можно использовать в Blueprint.
 * Эти функции предоставляют готовую логику, которую можно вызывать
 * из любого Blueprint без необходимости писать код на C++.
 * Удобно для группирования связанных функций в одном месте
 * (например, математические операции, работа со строками).
 */
UCLASS()
class MACROTEST_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// функция доступная в любом блюпринте
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Test")
	static FString GetAppVersion();

};
