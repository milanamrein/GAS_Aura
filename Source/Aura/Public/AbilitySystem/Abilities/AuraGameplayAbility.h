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
	/// Overridable Function to return the Ability's Description based on its Level
	/// </summary>
	/// <param name="Level"></param>
	/// <returns></returns>
	virtual FString GetDescription(int32 Level);

	/// <summary>
	/// Overridable Function to return the Ability's Description for the next Level based on its Level
	/// </summary>
	virtual FString GetNextLevelDescription(int32 Level);

	/// <summary>
	/// Static Function to return the Description for a Locked Ability based on its next Level
	/// </summary>
	static FString GetLockedDescription(int32 NextLevel);

protected:

	/// <summary>
	/// Function to get the Mana Cost for this Ability based on its Level
	/// </summary>
	/// <returns></returns>
	float GetManaCost(float InLevel = 1.f) const;
	
	/// <summary>
	/// Function to get the Cooldown for this Ability based on its Level
	/// </summary>
	/// <returns></returns>
	float GetCooldown(float InLevel = 1.f) const;
};
