// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 * Class to determine global members for the AbilitySystem used in the game
 */
UCLASS()
class AURA_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	/** Function that sets the global GameplayEffectContext */
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};
