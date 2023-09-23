// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IHighlightInterface;

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

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	/// <summary>
	/// Function to bind to the Move Input Action
	/// </summary>
	void Move(const FInputActionValue& InputActionValue);

	/// <summary>
	/// Function to trace highlightable objects with the mouse cursor
	/// </summary>
	void CursorTrace();

	/// <summary>
	/// Pointer to the Actor that was highlighted in the last frame
	/// </summary>
	IHighlightInterface* LastActor;

	/// <summary>
	/// Pointer to the Actor that is currently highlighted in this frame
	/// </summary>
	IHighlightInterface* ThisActor;
};
