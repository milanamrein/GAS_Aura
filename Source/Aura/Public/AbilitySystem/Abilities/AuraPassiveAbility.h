// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraPassiveAbility.generated.h"

/**
 * Base class for Passive Abilities
 */
UCLASS()
class AURA_API UAuraPassiveAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	/// <summary>
	/// Callback function to when this Passive Ability is being deactivated
	/// </summary>
	void ReceiveDeactivate(const FGameplayTag& AbilityTag);

};
