// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

// Delegate type for broadcasting the Asset Tags
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

/**
 * Component class for GAS
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Callback function to when the Ability Actor Info is set
	/// on Characters
	/// </summary>
	void AbilityActorInfoSet();

	/// <summary>
	/// Delegate for broadcasting Asset Tags
	/// </summary>
	FEffectAssetTags EffectAssetTags;

	/// <summary>
	/// Function to grant Gameplay Abilities to Characters
	/// </summary>
	/// <param name="Abilities">Abilities to grant</param>
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);

	/// <summary>
	/// Function to Activate Abilities when the InputTag is Held or Pressed
	/// </summary>
	/// <param name="InputTag">The InputTag the Ability has</param>
	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	/// <summary>
	/// Function to Activate Abilities when the InputTag is Released
	/// </summary>
	/// <param name="InputTag">The InputTag the Ability has</param>
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

protected:

	/// <summary>
	/// Client RPC to when a GameplayEffect is applied to this AbilitySystemComponent
	/// </summary>
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

};
