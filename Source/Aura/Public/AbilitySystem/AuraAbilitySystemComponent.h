// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

// Delegate type for broadcasting the Asset Tags
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

// Delegate type for broadcasting when our Abilities have been given
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven, UAuraAbilitySystemComponent*);

// Delegate type for each Ability
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec& /*AbilitySpec*/);

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
	FEffectAssetTags EffectAssetTagsDelegate;

	/// <summary>
	/// Delegate for broadcasting when our Abilities have been given on startup
	/// </summary>
	FAbilitiesGiven AbilitiesGivenDelegate;

	/// <summary>
	/// Function to grant Gameplay Abilities to Characters
	/// </summary>
	/// <param name="Abilities">Abilities to grant</param>
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);

	/// <summary>
	/// Function to grant passive Gameplay Abilities to Characters
	/// </summary>
	/// <param name="Abilities">Passive Abilities to grant</param>
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& PassiveAbilities);

	/// <summary>
	/// Boolean for whether or not the startup Abilities have been given
	/// to the AbilitiesGivenDelegate and been broadcasted.
	/// Binding to AbilitiesGivenDelegate can happen too late or too early.
	/// </summary>
	bool bStartupAbilitiesGiven = false;

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

	/// <summary>
	/// Function that takes in an FForEachAbility delegate and call the function 
	/// that is bound to it for each Ability of this ASC
	/// </summary>
	void ForEachAbility(const FForEachAbility& Delegate);

	/// <summary>
	/// Function for getting the Tag of any given Spec 
	/// </summary>
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	/// <summary>
	/// Function for getting the InputTag of any given Spec 
	/// </summary>
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
protected:

	/// <summary>
	/// Replicates ActivatableAbilities. Triggered when we give Abilities in
	/// AddCharacterAbilities(). This way GivenAbilities can be replicated.
	/// </summary>
	virtual void OnRep_ActivateAbilities() override;

	/// <summary>
	/// Client RPC to when a GameplayEffect is applied to this AbilitySystemComponent
	/// </summary>
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

};
