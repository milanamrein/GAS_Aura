// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IHighlightInterface;
class UAuraInputConfig;
struct FGameplayTag;
class UAuraAbilitySystemComponent;
class USplineComponent;
class UDamageTextComponent;

/**
 * Player Controller class for Aura
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime);

	/// <summary>
	/// Client RPC to spawn and show the Damage
	/// on the owning Client's HUD
	/// </summary>
	/// <param name="DamageAmount">Amount of Damage</param>
	/// <param name="TargetCharacter">Character being hit by Damage Amount</param>
	/// <param name="bBlockedHit">Whether or not we had a Blocked Hit</param>
	/// <param name="bCriticalHit">Whether or not we had a Critical Hit</param>
	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	/// <summary>
	/// Input Action for moving the Pawn
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	/// <summary>
	/// Function to bind to the Move Input Action
	/// </summary>
	void Move(const FInputActionValue& InputActionValue);

	/// <summary>
	/// Input Action for pressing Shift to spawn Projectile
	/// when clicking LMB
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	/// <summary>
	/// Boolean for whether the Shift key is being held
	/// </summary>
	bool bShiftKeyDown = false;

	/// <summary>
	/// Function to bind to the Shift Input Action when it is started
	/// </summary>
	void ShiftPressed() { bShiftKeyDown = true; };
	
	/// <summary>
	/// Function to bind to the Shift Input Action when it is completed
	/// </summary>
	void ShiftReleased() { bShiftKeyDown = false; };

	/// <summary>
	/// Variable for Hit Result under Cursor
	/// </summary>
	FHitResult CursorHit;

	/// <summary>
	/// Function to trace highlightable objects with the mouse cursor
	/// </summary>
	void CursorTrace();

	/// <summary>
	/// Pointer to the Actor that was highlighted in the last frame
	/// </summary>
	TObjectPtr<IHighlightInterface> LastActor;

	/// <summary>
	/// Pointer to the Actor that is currently highlighted in this frame
	/// </summary>
	TObjectPtr<IHighlightInterface> ThisActor;

	/// <summary>
	/// Input Configuration Data Asset
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	/// <summary>
	/// Pointer to the Ability System Component
	/// </summary>
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();

	/**
	* Callback functions to Ability Input Actions
	*/

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	/**
	* Click to Move
	*/

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTimeSec = 0.f;
	float ShortPressThresholdSec = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	/// <summary>
	/// Function to handle auto running (click to move)
	/// </summary>
	void AutoRun();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
