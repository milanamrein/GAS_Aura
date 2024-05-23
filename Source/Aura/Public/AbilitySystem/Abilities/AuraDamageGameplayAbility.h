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
	/// <returns></returns>
	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr) const;

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
