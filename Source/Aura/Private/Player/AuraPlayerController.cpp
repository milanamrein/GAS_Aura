// Copyright Milán Amrein


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/HighlightInterface.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "AuraGameplayTags.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRun();
}

void AAuraPlayerController::CursorTrace()
{
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

	if (LastActor != ThisActor) {
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;

	if (APawn* ControlledPawn = GetPawn()) {
		// Get location on the Spline closest to the Pawn
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		// Get direction corresponding to the closest location
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		// Move Pawn to direction
		ControlledPawn->AddMovementInput(Direction);

		// Check distance to destination
		const float DistanceToDest = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDest <= AutoRunAcceptanceRadius) { // should no longer be auto running
			bAutoRunning = false;
		}
	}
}

void AAuraPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit)
{
	if (!IsValid(TargetCharacter) || DamageTextComponentClass == nullptr || !IsLocalController()) return;

	// Construct && Register Widget Component
	UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
	DamageText->RegisterComponent(); // need to do this manually if we do not create the component in the constructor
	// Attach it to Target's Root who is taking the Damage
	DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	// Detach it to "float away" according to its animation
	DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	DamageText->SetDamageText(DamageAmount, bBlockedHit, bCriticalHit); // Set Damage Text
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// halt execution if input context is invalid
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem) { // this will be valid on local machine in multiplayer
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
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

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent); // halts execution if cast fails
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftPressed);
	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftReleased);

	// Bind callbacks to Ability Input Actions
	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed,
		&ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
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

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr) {
		AuraAbilitySystemComponent = 
			Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)) {
		// Set whether we are targeting an Enemy or not with LMB
		bTargeting = ThisActor ? true : false;
		// We should be not auto running yet when we've just pressed our LMB
		bAutoRunning = false;
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;

	// We don't want any of the below functionality if the Input is not LMB
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)) {
		GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}

	GetASC()->AbilityInputTagReleased(InputTag);
	if (!bTargeting && !bShiftKeyDown) { // when we are not targeting with LMB or pressing Shift key; moving
		const APawn* ControlledPawn = GetPawn();
		// Check if it was a short press
		if (FollowTimeSec <= ShortPressThresholdSec && ControlledPawn) {
			// Create a navigation path (set of points to follow)
			// Need to set Allow Client Side Navigation to true in Project Settings for this to work on the client
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination)) {
				// Add set of points to the Spline
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints) {
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				}
				if (NavPath->PathPoints.Num() > 0) {
					// Set Destination to last path point for auto run check in AutoRun()
					CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
					bAutoRunning = true;
				}
			}
		}
		FollowTimeSec = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;

	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)) {
		GetASC()->AbilityInputTagHeld(InputTag);
	} else if (bTargeting || bShiftKeyDown) { // when we are targeting an Enemy with LMB or holding the Shift key down
		GetASC()->AbilityInputTagHeld(InputTag);
	} else { // when we are not targeting with LMB
		FollowTimeSec += GetWorld()->GetDeltaSeconds(); // increase FollowTime as we are holding LMB down

		// Cache destination we are moving towards
		if (CursorHit.bBlockingHit) {
			CachedDestination = CursorHit.ImpactPoint;
		}

		// Move Pawn towards Destination
		if (APawn* ControlledPawn = GetPawn()) {
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}
