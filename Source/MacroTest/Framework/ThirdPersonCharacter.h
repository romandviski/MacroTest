// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ThirdPersonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
*  Character — это расширение класса Pawn, предназначенное для управления игровыми персонажами.
*  Он включает встроенные функции для передвижения, анимации и взаимодействия с миром.
*/
UCLASS(config=Game)
class AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	/** Стрела камеры позиционирует камеру позади персонажа */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings | Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings | Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings | Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings | Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AThirdPersonCharacter();

protected:
	// Для добавления контекста
	virtual void BeginPlay() override;
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/** Вызывается для ввода движения */
	void Move(const FInputActionValue& Value);
	/** Вызывается для просмотра ввода */
	void Look(const FInputActionValue& Value);

public:
	/** Возвращает подобъект CameraBoom **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Возвращает подобъект FollowCamera **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
