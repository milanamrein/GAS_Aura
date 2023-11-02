// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;
class UAttributeMenuWidgetController;
class UAbilitySystemComponent;

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

	/// <summary>
	/// Function to initialize default Attributes based on a Character Class and Level
	/// </summary>
	/// <param name="WorldContextObject">World Context object reference</param>
	/// <param name="CharacterClass">Character's Class</param>
	/// <param name="Level">Character's Level</param>
	/// <param name="ASC">AbilitySystemComponent to apply Gameplay Effects on</param>
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

};
