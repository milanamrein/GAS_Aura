// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;
class UAttributeMenuWidgetController;

/**
 * Blueprint Library for the game's AbilitySystem
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Static Getter for the Overlay Widget Controller.
	/// Should be called only from a Widget. Only exists for the Local Player.
	/// </summary>
	/// <param name="WorldContextObject">World Context object reference</param>
	/// <returns>Overlay Widget Controller</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	/// <summary>
	/// Static Getter for the Attribute Menu Widget Controller.
	/// Should be called only from a Widget. Only exists for the Local Player.
	/// </summary>
	/// <param name="WorldContextObject">World Context object reference</param>
	/// <returns>AttributeMenu Widget Controller</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

};
