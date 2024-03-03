// Copyright Milán Amrein


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Aura/AuraLogChannels.h"
#include "Interaction/PlayerInterface.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	// Bind delegates
	// OnGameplayEffectAppliedDelegateToSelf only gets called on the server so we bind a Client RPC to it so it gets called on the Owning Client
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClientEffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : Abilities) {
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability)) {
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag); // add the AuraAbility's StartupInputTag to the list of Ability Tags
			GiveAbility(AbilitySpec);
		}
	}

	bStartupAbilitiesGiven = true;
	AbilitiesGivenDelegate.Broadcast(this);
}

void UAuraAbilitySystemComponent::AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& PassiveAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : PassiveAbilities) {
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbilityAndActivateOnce(AbilitySpec); // activate Passive Ability
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	// Check whether this ASC has any activatable abilities with this InputTag
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities()) {
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) && !AbilitySpec.IsActive()) { // only activate if it is not active
			AbilitySpecInputPressed(AbilitySpec); // keeps track of whether or not the Ability's input has been pressed
			TryActivateAbility(AbilitySpec.Handle); // function to Activate an Ability
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	// Check whether this ASC has any activatable abilities with this InputTag
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities()) {
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) {
			AbilitySpecInputReleased(AbilitySpec); // keeps track of whether or not the Ability's input has been released
		}
	}
}

void UAuraAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
	// Lock in Abilities because they can change status so this is good practice before looping through them
	FScopedAbilityListLock ActiveScopeLock(*this);

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities()) {
		if (!Delegate.ExecuteIfBound(AbilitySpec)) {
			// Log function name in case the Delegate binding didn't happen
			UE_LOG(LogAura, Error, TEXT("Failed to execute delegate in %hs"), __FUNCTION__);
		}
	}
}

FGameplayTag UAuraAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (AbilitySpec.Ability) {
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags) {
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities")))) { // if the Tag's name has "Abilities" in it
				return Tag;
			}
		}
	}

	return FGameplayTag();
}

FGameplayTag UAuraAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (FGameplayTag Tag : AbilitySpec.DynamicAbilityTags) {
		// we should have only 1 InputTag at a time for an Ability
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag")))) {
			return Tag;
		}
	}

	return FGameplayTag();
}

void UAuraAbilitySystemComponent::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	// Check if there's any Attribute Points
	if (GetAvatarActor()->Implements<UPlayerInterface>() && IPlayerInterface::Execute_GetAttributePoints(GetAvatarActor()) > 0) {
		ServerUpgradeAttribute(AttributeTag);
	}
}

void UAuraAbilitySystemComponent::ServerUpgradeAttribute_Implementation(const FGameplayTag& AttributeTag)
{
	if (GetAvatarActor()->Implements<UPlayerInterface>()) {
		// Send Event to the Player's Passive Gameplay Ability ListenForEvents to upgrade Attribute
		FGameplayEventData Payload;
		Payload.EventTag = AttributeTag;
		Payload.EventMagnitude = 1.f;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(), AttributeTag, Payload);

		// Decrease Attribute Points because the Player is spending 1
		IPlayerInterface::Execute_AddToAttributePoints(GetAvatarActor(), -1);
	}
}

void UAuraAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	if (!bStartupAbilitiesGiven) { // only want to replicate the broadcast the first time, don't want to replicate it every time
		bStartupAbilitiesGiven = true;
		AbilitiesGivenDelegate.Broadcast(this);
	}
}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	// Get all tags and broadcast them to WidgetController
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsDelegate.Broadcast(TagContainer);
}
