// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

// описываем собственный энумератор
UENUM(BlueprintType)
enum class ETestEnumerator : uint8 // название начинается с E, потому что это энумератор
{
	Ver1 UMETA(DisplayName = "Вариант 1"),
	Ver2 UMETA(DisplayName = "Вариант 2"),
	Ver3 UMETA(DisplayName = "Вариант 3"),
};

UCLASS()
class MACROTEST_API ATestActor : public AActor
{
	GENERATED_BODY()
	
private: // Доступ открыт только самому классу
	
	// Описываем состав компонентов нашего будущего актора
	UPROPERTY(EditDefaultsOnly, Category = Components)
	USceneComponent* SceneComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* StaticMesh;
	
	// Полностью приватная переменная, блюпринт о ней ничего не знает
	int FirstSecretInt = 555;

	// Переменная будет видна в блюпринте, как и этот комментарий =)
	// но её нельзя изменять на сцене
	UPROPERTY(EditDefaultsOnly, Category = "Test | Private", meta = (AllowPrivateAccess = true))
	int SecondSecretInt = 777;
	// Переменная будет видна в блюпринте, редактировать её будет нельзя
	UPROPERTY(VisibleAnywhere, Category = "Test | Private", meta = (AllowPrivateAccess = true))
	float FinalDamage = 0;
	
public: // Доступ открыт всем другим классам, кто видит определение данного класса
	ATestActor();

protected: // Доступ открыт классам, производным от данного (наследникам)

	// Вызывается после инициализации переменных
	// Например, для настройки компонентов на основе свойств
	virtual void PostInitProperties() override;

	// Вызывается после изменений в редакторе
	// Например, когда вы изменяете значение свойства в панели Details в Unreal Editor.
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	// Оверрайд констракш скрипта из блюпринтов
	virtual void OnConstruction(const FTransform& Transform) override;

	// Вызывается при порождении в мире(спавне или старте игры)
	virtual void BeginPlay() override;
	// Вызывается каждый кадр
	virtual void Tick(float DeltaTime) override;
	// Вызывается перед разрушением актора 
	virtual void Destroyed() override;

public: // Доступ открыт всем другим классам, кто видит определение данного класса
	
// Мои переменные =========================================================================================================
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test | Base", meta = (ToolTip = "Тестовый инт"))
		int32 IntBlueprintReadWrite = 2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test | Base")
		int32 IntBlueprintReadOnly = 3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Test | Base")
		int32 IntVisibleAnywhere = 777;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test | Base")
		bool AdditionalOption = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test | Base", meta = (EditCondition = AddiTionalOption, EditConditionHides))
		int32 IntAdditionalOption = 7;

	// Примеры для PostEditChangeProperty
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test | PostEdit")
		float BaseDamage = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test | PostEdit")
		float Multiplier = 3;

	// Энумератор описан перед классом вверху
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test | Enumerator")
		ETestEnumerator CoolEnumerator = ETestEnumerator::Ver1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test | Enumerator", meta = (EditCondition = "CoolEnumerator == ETestEnumerator::Ver3", EditConditionHides))
		int32 IntOtherAdditionalOption = 7;
	
// Мои функции =========================================================================================================

	// Обычная С++ функция, блюпринт ничего о ней не знает
	void SimpleCppFunction();
	// Функция о которой ничего не знает блюпринт, но знает система рефлексии
	UFUNCTION() void JustMyParameterFunction(int32 X, float Y, FString Z);
	// Функция объявленная в С++ и доступная в блюпринт наследнике
	UFUNCTION(BlueprintCallable, Category = "Test | Functions", meta = (Keywords = "my, function, example", Tooltip = "Пример функции"))
	void SimpleCallableFunction();

	/*
	 * С++ функция с параметрами доступная в блюпринт наследнике
	 * const у функции означает что функция не изменяет состояние объекта
	 * const у параметров гарантирует неизменность этих параметров внутри функции
	 */
	UFUNCTION(BlueprintCallable, Category = "Test | Functions")
	int CallableParameterFunction(const int32 X, const float Y, const FString Z = "Имя") const;

	/**
	 * С++ функция возвращающая 4 параметра, 3 из них при помощи ссылок
	 * @param X Какой-то int 
	 * @param Z Какой-то FString
	 * @return Возвращает статус
	 */
	UFUNCTION(BlueprintCallable, Category = "Test | Functions")
	bool ThreeParameterFunction(int32& X, FString& Z) const;
	
	/*
	 * Часть логики в С++, продолжение в блюпринте
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Test", meta = (Keywords = "777, fun"))
	void BlueprintNativeEventFunction();

	// см. ToolTip
	UFUNCTION(BlueprintImplementableEvent, Category = "Test | Function", meta = (ToolTip = "Логика только в блюпринте"))
	void BlueprintImplementableEventFunction();
	
	// Пьюр функция объявленная в С++ (нода без входа)
	UFUNCTION(BlueprintPure, Category = "Test | PureFunctions")
	int32 SimplePureFunction() const;
	// Статик пьюр функция с параметрами
	// Ключевое слово static делает функцию принадлежащей классу, а не объекту.
	// Полезны для вызова без создания объекта и для утилитарных задач, не зависящих от состояния объекта.
	UFUNCTION(BlueprintPure, Category = "Test | PureFunctions")
	static FVector PureParameterFunction(const float X, const float Y, const float Z);

	// Компактная пьюр функция
	// Ещё примеры	https://nerivec.github.io/old-ue4-wiki/pages/custom-blueprint-node-creation.html
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Adds floats", CompactNodeTitle = "Math Floats", Keywords = "Float Add"), Category =  "Test | PureFunctions")
	static float MathFloats(float A = 0.1f, float B = 0.2f);

	// FORCEINLINE - Если компилятор решает, что встраивание возможно и целесообразно, 
	// то он заменяет каждый вызов функции на непосредственное вставление кода функции в место вызова.
	UFUNCTION(BlueprintPure, Category = "Test | PureFunctions")
	FORCEINLINE int32 MyFastBlueprintPureReturnFunction() const { return FirstSecretInt; }

};
