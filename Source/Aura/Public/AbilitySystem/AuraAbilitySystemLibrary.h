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

	/// <summary>
	/// Function to initialize Enemy Gameplay Abilities
	/// </summary>
	/// <param name="WorldContextObject">World Context object reference</param>
	/// <param name="ASC">AbilitySystemComponent to apply Gameplay Abilities on</param>
	/// <param name="CharacterClass">Character's Class</param>
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass);

	/// <summary>
	/// Function to get the Character Class Info Data Asset
	/// </summary>
	/// <param name="WorldContextObject">World Context object reference</param>
	/// <returns>CharacterClassInfo Data Asset</returns>
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	/// <summary>
	/// Function to get whether or not we have a Blocked Hit based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to get the Blocked Hit from</param>
	/// <returns>Whether or not we have a Blocked Hit</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	/// <summary>
	/// Function to get whether or not we have a Critical Hit based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to get the Critical Hit from</param>
	/// <returns>Whether or not we have a Critical Hit</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	/// <summary>
	/// Function to set the result of Blocked Hit
	/// </summary>
	/// <param name="EffectContextHandle">GE Context to set the Blocked Hit result on</param>
	/// <param name="bInIsBlockedHit">The result of Blocked Hit</param>
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit); // non-const ref is an output pin by default in BP

	/// <summary>
	/// Function to set the result of Critical Hit
	/// </summary>
	/// <param name="EffectContextHandle">GE Context to set the Critical Hit result on</param>
	/// <param name="bInIsCriticalHit">The result of Critical Hit</param>
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	/// <summary>
	/// Function to get all Players within an invisible Sphere
	/// </summary>
	/// <param name="WorldContextObject">World Context object reference</param>
	/// <param name="OutOverlappingActors">Array containing all Actors within the Sphere</param>
	/// <param name="ActorsToIgnore">Actors that are within the Sphere but ignored</param>
	/// <param name="Radius">Sphere Radius</param>
	/// <param name="SphereOrigin">Sphere Center location</param>
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin);

	/// <summary>
	/// Function to check whether 2 Actors are friends or not
	/// </summary>
	/// <returns>True if they are friends </returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static bool IsFriend(AActor* FirstActor, AActor* SecondActor);
};
