// © 2024, Mikhail Efremov. All rights reserved.

#include "TestActor.h"

ATestActor::ATestActor()
{
	// Выключаем тик, если он нам не нужен
	PrimaryActorTick.bCanEverTick = false;

	// Устанавливаем компонент сцены и устанавливаем как рутовый(корневой) компонент
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	//RootComponent = SceneComponent; // ещё вариант, но эпики иногда закрывают прямой доступ к переменным
	
	// Создаём статик меш компонент и настраиваем
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	// ConstructorHelpers помогает назначить ассет из С++ кода, плохо т.к. адрес ассета увековечен в исходном коде
	static ConstructorHelpers::FObjectFinder<UStaticMesh>VisualAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if(VisualAsset.Succeeded())
		StaticMesh->SetStaticMesh(VisualAsset.Object);
	// приклеиваем StaticMesh к рутовому компоненту
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetRelativeLocation(FVector(0,0,50));
}

void ATestActor::PostInitProperties()
{
	Super::PostInitProperties();
}

void ATestActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// Код для обработки изменения свойства
	if (PropertyChangedEvent.Property != nullptr)
	{
		const FName PropertyName = PropertyChangedEvent.Property->GetFName();
		if (PropertyName == GET_MEMBER_NAME_CHECKED(ATestActor, BaseDamage) ||
			PropertyName == GET_MEMBER_NAME_CHECKED(ATestActor, Multiplier))
		{
			// Реагируем на изменение только BaseDamage и Multiplier
			FinalDamage = BaseDamage * Multiplier;
		}
	}
}

void ATestActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATestActor::Destroyed()
{
	// Свою логику надо размещать пока актор ещё существует
	// до вызова родителькой
	Super::Destroyed();
}

void ATestActor::SimpleCppFunction()
{
	// блюпринт ничего о ней не знает
}

void ATestActor::JustMyParameterFunction(int32 X, float Y, FString Z)
{
	// блюпринт ничего о ней не знает, система рефлексии знает
}

void ATestActor::SimpleCallableFunction()
{
	// Какой-то функционал
}

int ATestActor::CallableParameterFunction(const int32 X, const float Y, const FString Z) const
{
	// Обязательна должна что-то возвращать
	return FirstSecretInt;
}

bool ATestActor::ThreeParameterFunction(int32& X, FString& Z) const
{
	// Внутрь по ссылке передаётся переменная и мы задаём ей значение
	X = FMath::RandRange(0, 100);
	Z = "Оля, ля!";
	// Обязательна должна что-то возвращать
	return X > 0;
}

void ATestActor::BlueprintNativeEventFunction_Implementation()
{
	// Обязательно на конце _Implementation
}

int32 ATestActor::SimplePureFunction() const
{
	// Обязательна должна что-то возвращать
	return FirstSecretInt;
}

FVector ATestActor::PureParameterFunction(const float X, const float Y, const float Z) 
{
	return FVector(X, Y, Z);
}

float ATestActor::MathFloats(const float A, const float B)
{
	return A + B;
}

