// Copyright Milán Amrein


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/HighlightInterface.h"

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

	// halt execution if input context is invalid
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // don't lock mouse to the viewport
	InputModeData.SetHideCursorDuringCapture(false); // don't hide the cursor once it is captured
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent); // halts execution if cast fails
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// Get rotation
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);

	// Get forward and right vectors
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Add movement to direction
	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return; // if we didn't hit any highlightable object

	LastActor = ThisActor;
	ThisActor = Cast<IHighlightInterface>(CursorHit.GetActor());

	/**
	* Line trace from cursor. Scenarios:
	* 1. LastActor is null and ThisActor is null
	*	- Do nothing
	* 2. LastActor is null and ThisActor is valid
	*	- Highlight ThisActor
	* 3. LastActor is valid and ThisActor is null
	*	- Unhighlight LastActor
	* 4. Both Actors are valid, but LastActor is not equal to ThisActor
	*	- Unhighlight LastActor
	*	- Highlight ThisActor
	* 5. Both Actors are valid and are the same Actor
	*	- Do nothing
	*/

	if (LastActor == nullptr && ThisActor != nullptr) {
		// Case 2.
		ThisActor->HighlightActor();
	}
	else if (LastActor != nullptr && ThisActor == nullptr) {
		// Case 3.
		LastActor->UnHighlightActor();
	}
	else if (LastActor != ThisActor) {
		// Case 4.
		LastActor->UnHighlightActor();
		ThisActor->HighlightActor();
	}
}
