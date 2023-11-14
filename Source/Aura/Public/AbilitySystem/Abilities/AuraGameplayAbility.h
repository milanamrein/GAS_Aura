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

	/// <summary>
	/// Variable for storing Gameplay Ability Damage. Can scale to different kinds of Abilities.
	/// Could be a member of a general GameplayAbility class specific to causing Damage as not all
	/// Abilities are going to cause Damage.
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat Damage;

};
