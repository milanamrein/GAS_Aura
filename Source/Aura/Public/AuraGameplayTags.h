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
	* Meta
	*/

	FGameplayTag Attributes_Meta_IncomingXP;

	/**
	* Inputs
	*/

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_Passive_1;
	FGameplayTag InputTag_Passive_2;

	/**
	* Damage Types
	*/

	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;

	/**
	* Resistance Types
	*/

	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Physical;

	/**
	* Debuff Types
	*/

	FGameplayTag Debuff_Burn;
	FGameplayTag Debuff_Stun;
	FGameplayTag Debuff_Arcane;
	FGameplayTag Debuff_Physical;

	FGameplayTag Debuff_Info_Chance;
	FGameplayTag Debuff_Info_Damage;
	FGameplayTag Debuff_Info_Frequency;
	FGameplayTag Debuff_Info_Duration;


	/// <summary>
	/// TMap for mapping all the Damage types with their respective Resistance type.
	/// <para>Key: Damage Type</para>
	/// <para>Value: Resistance Type</para>
	/// </summary>
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	/// <summary>
	/// TMap for mapping all the Damage types with their respective Debuff type.
	/// <para>Key: Damage Type</para>
	/// <para>Value: Debuff Type</para>
	/// </summary>
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;

	/**
	* Effects
	*/

	FGameplayTag Effects_HitReact;

	/**
	* Abilities
	*/

	FGameplayTag Abilities_None;

	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;

	FGameplayTag Abilities_HitReact;

	FGameplayTag Abilities_Status_Locked;
	FGameplayTag Abilities_Status_Eligible;
	FGameplayTag Abilities_Status_Unlocked;
	FGameplayTag Abilities_Status_Equipped;

	FGameplayTag Abilities_Type_Offensive;
	FGameplayTag Abilities_Type_Passive;
	FGameplayTag Abilities_Type_None;

	FGameplayTag Abilities_Fire_FireBolt;
	FGameplayTag Abilities_Fire_FireBlast;
	FGameplayTag Abilities_Lightning_Electrocute;
	FGameplayTag Abilities_Arcane_ArcaneShards;

	FGameplayTag Abilities_Passive_HaloOfProtection;
	FGameplayTag Abilities_Passive_LifeSiphon;
	FGameplayTag Abilities_Passive_ManaSiphon;

	/**
	* Cooldowns
	*/

	FGameplayTag Cooldown_Fire_FireBolt;

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

	FGameplayTag Player_Block_InputPressed;
	FGameplayTag Player_Block_InputHeld;
	FGameplayTag Player_Block_InputReleased;
	FGameplayTag Player_Block_CursorTrace;

	/**
	* Cues
	*/

	FGameplayTag GameplayCue_FireBlast;

private:

	/// <summary>
	/// Variable containing the Singleton
	/// </summary>
	static FAuraGameplayTags GameplayTags;
};
