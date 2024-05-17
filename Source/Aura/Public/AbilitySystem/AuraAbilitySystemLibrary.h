// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;
class UAttributeMenuWidgetController;
class UAbilitySystemComponent;
class USpellMenuWidgetController;
class UAbilityInfo;
struct FWidgetControllerParams;

/**
 * Blueprint Library for the game's AbilitySystem
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Function to create the FWidgetControllerParams struct and AuraHUD for each WidgetController
	/// </summary>
	/// <param name="WorldContextObject">World Context Object</param>
	/// <param name="OutWCParams">Struct to fill with required data</param>
	/// <param name="OutAuraHUD">Pointer reference to the HUD</param>
	/// <returns>Whether the creation of each required struct member was successful or not</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static bool CreateWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AAuraHUD*& OutAuraHUD);

	/// <summary>
	/// Static Getter for the Overlay Widget Controller.
	/// Should be called only from a Widget. Only exists for the Local Player.
	/// </summary>
	/// <param name="WorldContextObject">World Context object reference</param>
	/// <returns>Overlay Widget Controller</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	/// <summary>
	/// Static Getter for the Attribute Menu Widget Controller.
	/// Should be called only from a Widget. Only exists for the Local Player.
	/// </summary>
	/// <param name="WorldContextObject">World Context object reference</param>
	/// <returns>AttributeMenu Widget Controller</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	/// <summary>
	/// Static Getter for the Spell Menu Widget Controller.
	/// Should be called only from a Widget. Only exists for the Local Player.
	/// </summary>
	/// <param name="WorldContextObject">World Context object reference</param>
	/// <returns>SpellMenu Widget Controller</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContextObject);

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
	/// Function to get the Ability Info Data Asset
	/// </summary>
	/// <param name="WorldContextObject">World Context object reference</param>
	/// <returns>AbilityInfo Data Asset</returns>
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|AbilityDefaults")
	static UAbilityInfo* GetAbilityInfo(const UObject* WorldContextObject);

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
	/// Function to get whether or not we have a successful Debuff based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to get the Successful Debuff from</param>
	/// <returns>Whether or not we have a successful Debuff</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle);

	/// <summary>
	/// Function to get the amount of Debuff Damage based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to get the Debuff Damage from</param>
	/// <returns>The amount of Debuff Damage</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	/// <summary>
	/// Function to get the amount of Debuff Duration based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to get the Debuff Duration from</param>
	/// <returns>The amount of Debuff Duration</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle);

	/// <summary>
	/// Function to get the amount of Debuff Frequency based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to get the Debuff Frequency from</param>
	/// <returns>The amount of Debuff Frequency</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);

	/// <summary>
	/// Function to get the Tag of the Damage Type based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to get the Damage Type from</param>
	/// <returns>The type of Damage</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);

	/// <summary>
	/// Function to get the Death Impulse Vector based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to get the Death Impulse Vector from</param>
	/// <returns>The Death Impulse Vector</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle);

	/// <summary>
	/// Function to get the Knockback Vector based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to get the Knockback Vector from</param>
	/// <returns>The Knockback</returns>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static FVector GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle);

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
	/// Function to set whether or not we have a successful Debuff based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to set the Successful Debuff on</param>
	/// <param name="bInIsSuccessfulDebuff">The new Successful Debuff boolean</param>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsSuccessfulDebuff);

	/// <summary>
	/// Function to set the amount of Debuff Damage based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to set the Debuff Damage on</param>
	/// <param name="InDebuffDamage">New Amount of Debuff Damage</param>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDamage);

	/// <summary>
	/// Function to set the amount of Debuff Duration based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to set the Debuff Duration on</param>
	/// <param name="InDebuffDuration">New Amount of Debuff Duration</param>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDuration);

	/// <summary>
	/// Function to set the amount of Debuff Frequency based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to set the Debuff Frequency on</param>
	/// <param name="InDebuffFrequency">New Amount of Debuff Frequency</param>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffFrequency);

	/// <summary>
	/// Function to set the Tag of the Damage Type based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to set the Damage Type on</param>
	/// <param name="InDamageType">New Damage Type Tag</param>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType);

	/// <summary>
	/// Function to set the Death Impulse Vector based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to set the Death Impulse Vector on</param>
	/// <param name="InImpulse">New Death Impulse Vector</param>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpulse);

	/// <summary>
	/// Function to set the Knockback Vector based on the GE Context
	/// </summary>
	/// <param name="EffectContextHandle">GE Context Handle to set the Knockback Vector on</param>
	/// <param name="InForce">New Knockback Vector</param>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetKnockbackForce(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce);

	/// <summary>
	/// Function to apply a Damage Gameplay Effect on the Target Actor
	/// </summary>
	/// <param name="DamageEffectParams">Struct of params to create the Gameplay Effect from</param>
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);

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

	/// <summary>
	/// Function to calculate Rotators that are evenly spaced. Useful when spawning multiple Projectiles at once
	/// </summary>
	/// <param name="Forward">Forward Vector</param>
	/// <param name="Axis">Axis to rotate the Forward Vector around</param>
	/// <param name="Spread">Amount of Spread</param>
	/// <param name="NumRotators">Number of Rotators used</param>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static TArray<FRotator> EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators);

	/// <summary>
	/// Function to calculate Vectors that are evenly spaced. Useful when spawning multiple Projectiles at once
	/// </summary>
	/// <param name="Forward">Forward Vector</param>
	/// <param name="Axis">Axis to rotate the Forward Vector around</param>
	/// <param name="Spread">Amount of Spread</param>
	/// <param name="NumRotators">Number of Vectors used</param>
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static TArray<FVector> EvenlyRotatedVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors);

	/// <summary>
	/// Function that returns the XP Reward for a specific
	/// Character Class on a certain Level
	/// </summary>
	static int32 GetXPRewardForCharacterClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel);
};
