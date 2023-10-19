// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Singleton struct containing native Gameplay Tags (available in C++ and BP)
 */
struct FAuraGameplayTags
{
public:
	
	/// <summary>
	/// Static Getter for getting the one and only existing FAuraGameplayTags instance
	/// </summary>
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	
	/// <summary>
	/// Static function for initializing Gameplay Tags
	/// </summary>
	static void InitializeNativeGameplayTags();

	/**
	* Primary Attributes
	*/

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	/**
	* Secondary Attributes
	*/

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

protected:

private:

	/// <summary>
	/// Variable containing the Singleton
	/// </summary>
	static FAuraGameplayTags GameplayTags;
};
