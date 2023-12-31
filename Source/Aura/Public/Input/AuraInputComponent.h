// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AuraInputConfig.h"
#include "AuraInputComponent.generated.h"

/**
 * Custom Input Component class for handling functionality related to Input
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Template function which binds callback functions to InputActions
	/// </summary>
	/// <typeparam name="UserClass">Type of object needed for BindActions</typeparam>
	/// <typeparam name="PressedFuncType">Type of the function to bind for when an Input is pressed</typeparam>
	/// <typeparam name="ReleasedFuncType">Type of the function to bind for when an Input is released</typeparam>
	/// <typeparam name="HeldFuncType">Type of the function to bind for when an Input is held</typeparam>
	/// <param name="InputConfig">Data Asset containing InputActions with Gameplay Tags associated with them</param>
	/// <param name="Object">Object needed for BindActions</param>
	/// <param name="PressedFunc">Function to bind for when an Input is pressed</param>
	/// <param name="ReleasedFunc">Function to bind for when an Input is released</param>
	/// <param name="HeldFunc">Function to bind for when an Input is held</param>
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, 
		ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc,
	ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FAuraInputAction& Action : InputConfig->AbilityInputActions) {
		if (Action.InputAction && Action.InputTag.IsValid()) {
			if (PressedFunc) {
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}
			if (ReleasedFunc) {
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
			if (HeldFunc) {
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag); // Action.InputTag is the arg of the callback
			}
		}
	}
}
