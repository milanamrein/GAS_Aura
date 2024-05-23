// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

// Delegate type for broadcasting the Asset Tags
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

// Delegate type for broadcasting when our Abilities have been given
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);

// Delegate type for each Ability
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec& /*AbilitySpec*/);

// Delegate type for Ability Status changes
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged, const FGameplayTag& /*AbilityTag*/, const FGameplayTag& /*StatusTag*/, int32 /*AbilityLevel*/);

// Delegate type for Equipment Status changes
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped, const FGameplayTag& /*AbilityTag*/, const FGameplayTag& /*StatusTag*/, const FGameplayTag& /*InpuyTag*/, const FGameplayTag& /*PrevInpuyTag*/);

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
	/// Delegate for broadcasting when an Ability's Status changed
	/// </summary>
	FAbilityStatusChanged AbilityStatusChangedDelegate;

	/// <summary>
	/// Delegate for broadcasting when an Ability is being Equipped
	/// </summary>
	FAbilityEquipped AbilityEquippedDelegate;

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
	/// Function to Activate Abilities when the InputTag is Held
	/// </summary>
	/// <param name="InputTag">The InputTag the Ability has</param>
	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	/// <summary>
	/// Function to Activate Abilities when the InputTag is Pressed
	/// </summary>
	/// <param name="InputTag">The InputTag the Ability has</param>
	void AbilityInputTagPressed(const FGameplayTag& InputTag);

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
	
	/// <summary>
	/// Function to return an Ability's Status based on the Spec
	/// </summary>
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	/// <summary>
	/// Function to get the AbilitySpec based on the Ability Tag if this ASC
	/// has that Ability
	/// </summary>
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);

	/// <summary>
	/// Function to get the AbilityStatus based on the Ability Tag if this ASC
	/// has that Ability
	/// </summary>
	FGameplayTag GetStatusFromAbilityTag(const FGameplayTag& AbilityTag);

	/// <summary>
	/// Function to get the InputTag based on the Ability Tag if this ASC
	/// has that Ability
	/// </summary>
	FGameplayTag GetInputTagFromAbilityTag(const FGameplayTag& AbilityTag);

	/// <summary>
	/// Function to upgrade an Attribute using Attribute Points
	/// </summary>
	/// <param name="AttributeTag">Tag of the Attribute that is going to be upgraded</param>
	void UpgradeAttribute(const FGameplayTag& AttributeTag);

	/// <summary>
	/// Function to update Ability Statuses based on their Level requirements
	/// </summary>
	void UpdateAbilityStatuses(int32 Level);

	/// <summary>
	/// Server RPC to handle spending a Spell Point on a given Ability
	/// </summary>
	UFUNCTION(Server, Reliable)
	void ServerSpendSpellPoint(const FGameplayTag& AbilityTag);

	/// <summary>
	/// Server RPC to handle equipping an Ability
	/// </summary>
	/// <param name="AbilityTag">Ability to Equip</param>
	/// <param name="Slot">Slot InputTag chosen for the Ability</param>
	UFUNCTION(Server, Reliable)
	void ServerEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Slot);

	/// <summary>
	/// Get the Description for current and next Level
	/// for an Ability based on its Tag
	/// </summary>
	/// <returns>Whether or not the Descriptions for the Active Ability were fetched successfully</returns>
	bool GetDescriptionsByAbilityTag(const FGameplayTag& AbilityTag, FString& OutDescription, FString& OutNextLevelDescription);

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

	/// <summary>
	/// Server RPC to upgrade an Attribute based on
	/// an Attribute Tag. Attribute upgrade should only be
	/// happening on the server.
	/// </summary>
	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);

	/// <summary>
	/// Client RPC to broadcast the Ability Status change down to Owning Clients
	/// </summary>
	UFUNCTION(Client, Reliable)
	void ClientUpdateAbilityStatus(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel);

	/// <summary>
	/// Function to clear a Slot's InputTag on the EquippedSpellRow
	/// based on the Ability's Spec
	/// </summary>
	void ClearSlot(FGameplayAbilitySpec* Spec);

	/// <summary>
	/// Function to clear any Abilities of a given Slot 
	/// </summary>
	void ClearAbilitiesOfSlot(const FGameplayTag& Slot);

	/// <summary>
	/// Function to check whether an Ability has a certain Slot/InputTag
	/// </summary>
	static bool AbilityHasSlot(FGameplayAbilitySpec* Spec, const FGameplayTag& Slot);

	/// <summary>
	/// Client RPC to handle equipping an Ability
	/// </summary>
	UFUNCTION(Client, Reliable)
	void ClientEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot);

};
