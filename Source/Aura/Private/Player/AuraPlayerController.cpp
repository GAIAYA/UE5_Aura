// Copyright Gaia


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(subsystem)
		subsystem->AddMappingContext(AuraContext, 0);// 关联InputMappingContext到EnhancedInputLocalPlayerSubsystem

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI inputModeDatas;
	inputModeDatas.SetHideCursorDuringCapture(false);
	inputModeDatas.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(inputModeDatas);// 设置输入模式

}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);// 关联InputAction

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D inputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator controlRotation = GetControlRotation();
	const FRotator yawControlRotation = FRotator(0.f, controlRotation.Yaw, 0.f);

	const FVector forwardDirection = FRotationMatrix(yawControlRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawControlRotation).GetUnitAxis(EAxis::Y);

	if (APawn* controlPawn = GetPawn())
	{
		controlPawn->AddMovementInput(forwardDirection, inputAxisVector.Y);
		controlPawn->AddMovementInput(rightDirection, inputAxisVector.X); 
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult cursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);
	if (!cursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = cursorHit.GetActor();

	/**
	 * 根据连个Actor的“状态”，分几种情况
	 * 1、LastActor为空 && ThisActor为空						- 什么都不做
	 * 2、LastActor为空 && ThisActor有效						- 高亮ThisActor
	 * 3、LastActor有效 && ThisActor为空						- 取消高亮LastActor
	 * 4、LastActor和ThisActor都有效，但是LastActor!=ThisActor	- 取消高亮LastActor，同时高亮ThisActor
	 * 5、LastActor和ThisActor都有效，并且LastActor==ThisActor	- 什么都不做
	 */

	if (!LastActor)
	{
		if (ThisActor)
		{
			ThisActor->HighlightActor();
		}
	}
	else
	{
		if (!ThisActor)
		{
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
		}
	}
}
