// © 2024, Mikhail Efremov. All rights reserved.

#include "CPPCube.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Устанавливает значения по умолчанию для этого актора (конструктор класса)
ACPPCube::ACPPCube()
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
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>VisualAsset(TEXT("/Game/ThirdPerson/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer"));
	//if()
	//StaticMesh->SetStaticMesh(VisualAsset.Object);
	// приклеиваем StaticMesh к рутовому компоненту
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetRelativeLocation(FVector(0,0,50));

	// Создаём компонент лампочку, нужен #include "Components/PointLightComponent.h"
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(StaticMesh);
	PointLight->SetLightColor(FLinearColor(1,0,0,1), true);
	//PointLight->SetLightColor(FLinearColor::Red); // ещё вариант
	PointLight->SetVisibility(false);
	PointLight->SetRelativeLocation(FVector(0,0,100));

	// Создаём компонент коллижн бокс
	// Больше про коллижн бокс https://youtu.be/TRTqRuBHajw?t=461
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(StaticMesh);
	CollisionBox->SetBoxExtent(FVector(100,100,100), true);
	CollisionBox->SetRelativeLocation(FVector(0,0,50));

	// Подвязываем свою функцию на событие(диспатчер, делегат) оверлап компонента с чем либо
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACPPCube::MyBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ACPPCube::MyEndOverlap);
}

// Вызывается при порождении в мире(спавне или старте игры)
void ACPPCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Вызывается каждый кадр
void ACPPCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// В нашем случае всё равно отключено в конструкторе класса
}

// Собственная функция для привязки к событию начало пересечения у компонента
void ACPPCube::MyBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	// нужен #include "Kismet/GameplayStatics.h"
	// нужен #include "GameFramework/Character.h"
	if(Cast<ACharacter>(OtherActor) == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		PointLight->SetVisibility(true);
	}
}

// Собственная функция для привязки к событию конец пересечения у компонента
void ACPPCube::MyEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if(Cast<ACharacter>(OtherActor) == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		PointLight->SetVisibility(false);
	}
}

// Переопределённая функция вызываемая при начале пересечения актора
// актор пересекается с кем то если один из его компонентов пересекается с чужим компонентом
void ACPPCube::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Переопределяю стандартные оверлапы актора (ActorBeginOverlap и ActorEndOverlap из блюпринтов)
	
	// Почти PrintString
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Hello! I override NotifyActorBeginOverlap =)");
	// больше про логирование
	// https://www.chrismccole.com/blog/logging-in-ue4-cpp
	// https://www.unrealcommunity.wiki/logging-lgpidy6i
}

// Переопределённая функция вызываемая при окончании пересечения актора
// актор пересекается с кем то если один из его компонентов пересекается с чужим компонентом
void ACPPCube::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Hello! I override NotifyActorEndOverlap =)");
}
