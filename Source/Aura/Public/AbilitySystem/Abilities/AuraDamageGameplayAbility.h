// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
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

protected:

	/// <summary>
	/// Class for the Damage Gameplay Effect
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	/// <summary>
	/// TMap for mapping Gameplay Ability Damage types as GameplayTags with their Damage values
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

	/// <summary>
	/// Function that returns a random Tagged Montage from a list of Montages
	/// </summary>
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
};
