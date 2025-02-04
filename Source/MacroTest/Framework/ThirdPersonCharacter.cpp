// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMacrosTestCharacter

AThirdPersonCharacter::AThirdPersonCharacter()
{
	// Выключаем тик, если он нам не нужен
	PrimaryActorTick.bCanEverTick = false;
	
	// Установите размер для капсулы столкновения
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Не вращайте камеру, когда вращается контроллер. Пусть это влияет только на камеру.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Настройка движения персонажа
	GetCharacterMovement()->bOrientRotationToMovement = true; // Персонаж движется в направлении ввода...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...при данной скорости вращения

	// Примечание: Для ускорения итераций эти и многие другие переменные можно настроить в чертеже персонажа
	// вместо того, чтобы перекомпилировать его.
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Создайте стрелу камеры (при столкновении притягивается к игроку)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // Камера следует на этом расстоянии за персонажем
	CameraBoom->bUsePawnControlRotation = true; // Поверните руку на основе контроллера

	// Создайте камеру слежения
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Прикрепите камеру к концу штанги и позвольте штанге регулироваться в соответствии с ориентацией контроллера
	FollowCamera->bUsePawnControlRotation = false; // Камера не поворачивается относительно руки

	// Примечание: ссылки на скелетную сетку и чертеж anim в компоненте Mesh (унаследованном от Character) 
	// устанавливаются в производном активе чертежа с именем ThirdPersonCharacter (чтобы избежать прямых ссылок на содержимое в C++).
}

void AThirdPersonCharacter::BeginPlay()
{
	// Вызовите базовый класс
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Система ввода

void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Добавляем Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Настройте привязку действий ввода к нужным функциям
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::Move);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Не удалось найти компонент Enhanced Input! Этот шаблон создан для использования системы Enhanced Input. Если вы планируете использовать устаревшую систему, то вам необходимо обновить этот файл C++."), *GetNameSafe(this));
	}
}

void AThirdPersonCharacter::Move(const FInputActionValue& Value)
{
	// Ввод это Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// узнайте, какой путь ведет вперед
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// получить forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// получить right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// добавить движение
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AThirdPersonCharacter::Look(const FInputActionValue& Value)
{
	// Ввод это Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// добавьте входные сигналы рысканья и тангажа в контроллер
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
