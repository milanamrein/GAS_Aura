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

	/**
	* Resistance Types
	*/

	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Physical;

	/**
	* Inputs
	*/

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	/**
	* Damage Types
	*/

	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;

	/// <summary>
	/// TMap for mapping all the Damage types with their respective Resistance type.
	/// <para>Key: Damage Type</para>
	/// <para>Value: Resistance Type</para>
	/// </summary>
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	/**
	* Effects
	*/

	FGameplayTag Effects_HitReact;

	/**
	* Abilities
	*/

	FGameplayTag Abilities_Attack;

	/**
	* Sockets & Montages
	*/

	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_Tail;
	
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

private:

	/// <summary>
	/// Variable containing the Singleton
	/// </summary>
	static FAuraGameplayTags GameplayTags;
};
