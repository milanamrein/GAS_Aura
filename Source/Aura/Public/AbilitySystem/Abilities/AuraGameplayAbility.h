// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * Base class for Gameplay Abilities
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Gameplay Tag for associating to this Ability if this Ability is a startup Ability
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;

};
