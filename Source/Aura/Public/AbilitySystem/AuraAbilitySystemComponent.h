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

protected:

	/// <summary>
	/// Callback function to when a GameplayEffect is applied to this AbilitySystemComponent
	/// </summary>
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

};
