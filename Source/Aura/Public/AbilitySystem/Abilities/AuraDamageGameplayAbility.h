// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * Gameplay Ability class capable of causing Damage
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Function to loop through all the Damage Types of an Ability and cause Damage
	/// </summary>
	/// <param name="TargetActor">Target to cause Damage to</param>
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
	
	
	/// <summary>
	/// Function to create FDamageEffectParams struct for applying Damages and Debuffs
	/// </summary>
	/// <param name="TargetActor">Optional: Target of the Effect</param>
	/// <param name="InRadialDamageOrigin">Optional: Origin of the Damage if it is a Radial Damage</param>
	/// <param name="bOverrideKnockbackDirection">Whether or not to override the direction of the Knockback</param>
	/// <param name="InKnockbackDirectionOverride">Vector to override the Knockback direction with</param>
	/// <param name="bOverrideDeathImpulse">Whether or not to override the direction of the Death Impulse</param>
	/// <param name="InDeathImpulseDirectionOverride">Vector to override the Death Impulse direction with</param>
	/// <param name="bOverridePitch">Whether or not to override the direction of Rotation Pitch</param>
	/// <param name="InPitchOverride">Amount to override Rotation Pitch with</param>
	/// <returns>Parameters for the Damage Effect</returns>
	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(
		AActor* TargetActor = nullptr, 
		FVector InRadialDamageOrigin = FVector::ZeroVector,
		bool bOverrideKnockbackDirection = false,
		FVector InKnockbackDirectionOverride = FVector::ZeroVector,
		bool bOverrideDeathImpulse = false,
		FVector InDeathImpulseDirectionOverride = FVector::ZeroVector,
		bool bOverridePitch = false,
		float InPitchOverride = 0.f
	) const;

	/// <summary>
	/// Function to return with the amount of Damage according to the Ability Level
	/// by GameplayTag
	/// </summary>
	UFUNCTION(BlueprintPure)
	float GetDamageAtLevel(const FGameplayTag& DamageTag) const;

protected:

	/// <summary>
	/// Class for the Damage Gameplay Effect
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	/// <summary>
	/// TMap for mapping Gameplay Ability Damages as GameplayTags with their Damage values.
	/// A Damage Ability can have multiple Damages.
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

	/// <summary>
	/// Amount of impulse an Enemy should have when
	/// receiving fatal damage
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DeathImpulseMagnitude = 1000.f;

	/// <summary>
	/// Amount of force an Enemy should have when
	/// receiving knockback
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat KnockbackForceMagnitude;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat KnockbackChance;

	/// <summary>
	/// Whether or not the Damage is a radial one
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	bool bIsRadialDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float RadialDamageInnerRadius = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float RadialDamageOuterRadius = 0.f;

	/// <summary>
	/// Possibility (percent) of Debuff
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Debuff")
	FScalableFloat DebuffChance;

	/// <summary>
	/// Amount a Debuff applies while it is active
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Debuff")
	FScalableFloat DebuffDamage;

	/// <summary>
	/// How frequently apply DebuffDamage in seconds
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Debuff")
	FScalableFloat DebuffFrequency;

	/// <summary>
	/// Amount of time (seconds) a Debuff is active for
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Debuff")
	FScalableFloat DebuffDuration;

	/// <summary>
	/// Function that returns a random Tagged Montage from a list of Montages
	/// </summary>
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;

	/// <summary>
	/// Function to get the Amount of Damage based on the Damage Type and
	/// the Ability's Level
	/// </summary>
	float GetDamageByType(float InLevel, const FGameplayTag& DamageType);
};
