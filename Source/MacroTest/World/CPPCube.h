// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPCube.generated.h"

// Предупреждаем компилятор что эти классы точно будут описаны позже
// forward declarations
// тут нет USceneComponent и UStaticMeshComponent,
// т.к. они уже подключены в родительском AActor
class UPointLightComponent;
class UBoxComponent;

UCLASS()
class MACROTEST_API ACPPCube : public AActor
{
	GENERATED_BODY()
	
private:
	// Описываем состав компонентов нашего будущего актора
	UPROPERTY(EditDefaultsOnly, Category = Components)
	USceneComponent* SceneComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* StaticMesh = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UPointLightComponent* PointLight = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UBoxComponent* CollisionBox = nullptr;

public:
	// Устанавливает значения по умолчанию для этого актора (конструктор класса)
	ACPPCube();

protected:
	// Вызывается при порождении в мире(спавне или старте игры)
	virtual void BeginPlay() override;
	// Вызывается каждый кадр
	virtual void Tick(float DeltaTime) override;

	// Переопределяю стандартные оверлапы актора (ActorBeginOverlap и ActorEndOverlap из блюпринтов)
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	// Пустой UFUNCTION() нужен для того что бы система рефлексии анрила знала про них
	// Собственные функции для подвязки на оверлапы компонента
	UFUNCTION()
	void MyBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void MyEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
