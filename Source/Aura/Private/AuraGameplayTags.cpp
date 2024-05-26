// Copyright Milán Amrein


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

// Explicitly declare the type for the static private member variable
FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	// Register Gameplay Tags using the Gameplay Tags Manager Singleton
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("Increases physical damage."));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("Increases magical damage."));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("Increases Armor and Armor Penetration."));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("Increases Health."));

	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves Block Chance."));
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("Ignores Percentage of enemy Armor, increases Critical Hit Chance."));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("Chance to cut incoming damage in half."));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("Chance to double damage plus critical hit bonus."));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("Bonus damage added when a critical hit is scored."));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("Reduces Critical Hit Chance of attacking enemies."));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("Amount of Health regenerated every 1 second."));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("Amount of Mana regenerated every 1 second."));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("Maximum amount of Health obtainable."));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("Maximum amount of Mana obtainable."));

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("InputTag.LMB"), FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("InputTag.RMB"), FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("InputTag.1"), FString("Input Tag for 1 key"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("InputTag.2"), FString("Input Tag for 2 key"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("InputTag.3"), FString("Input Tag for 3 key"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("InputTag.4"), FString("Input Tag for 4 key"));
	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("InputTag.Passive.1"), FString("Input Tag for Passive Ability 1"));
	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("InputTag.Passive.2"), FString("Input Tag for Passive Ability 2"));

	GameplayTags.Damage = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Damage"), FString("Damage"));
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Damage.Fire"), FString("Fire Damage Type"));
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Damage.Lightning"), FString("Lightning Damage Type"));
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Damage.Arcane"), FString("Arcane Damage Type"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Damage.Physical"), FString("Physical Damage Type"));

	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Resistance.Fire"), FString("Resistance to Fire Damage"));
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"), FString("Resistance to Lightning Damage"));
	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Resistance.Arcane"), FString("Resistance to Arcane Damage"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Resistance.Physical"), FString("Resistance to Physical Damage"));

	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Debuff.Burn"), FString("Burn Debuff for Fire Damage"));
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Debuff.Stun"), FString("Stun Debuff for Lightning Damage"));
	GameplayTags.Debuff_Arcane = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Debuff.Arcane"), FString("Debuff for Arcane Damage"));
	GameplayTags.Debuff_Physical = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Debuff.Physical"), FString("Debuff for Physical Damage"));

	GameplayTags.Debuff_Info_Chance = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Debuff.Info.Chance"), FString("Debuff Chance"));
	GameplayTags.Debuff_Info_Damage = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Debuff.Info.Damage"), FString("Debuff Damage"));
	GameplayTags.Debuff_Info_Duration = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Debuff.Info.Duration"), FString("Debuff Duration"));
	GameplayTags.Debuff_Info_Frequency = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Debuff.Info.Frequency"), FString("Debuff Frequency"));

	// Mapping Damage types to Resistances
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);

	// Mapping Damage types to Debuffs
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Fire, GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Lightning, GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Arcane, GameplayTags.Debuff_Arcane);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Physical, GameplayTags.Debuff_Physical);

	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"), FString("Incoming XP Meta Attribute"));

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Effects.HitReact"), FString("Tag granted when Hit Reacting"));

	GameplayTags.Abilities_None = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.None"), FString("No Ability - 'nullptr' for Ability Tags"));

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Attack"), FString("Attack Ability Tag"));
	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Summon"), FString("Summon Ability Tag"));

	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.HitReact"), FString("HitReact Ability Tag"));

	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Status.Eligible"), FString("Eligible Status"));
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Status.Equipped"), FString("Equipped Status"));
	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Status.Locked"), FString("Locked Status"));
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Status.Unlocked"), FString("Unlocked Status"));

	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Type.None"), FString("None Type"));
	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Type.Offensive"), FString("Offensive Type"));
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Type.Passive"), FString("Passive Type"));

	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"), FString("FireBolt Ability Tag"));
	GameplayTags.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Lightning.Electrocute"), FString("Electrocute Ability Tag"));

	GameplayTags.Abilities_Passive_HaloOfProtection = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Passive.HaloOfProtection"), FString("Halo Of Protection"));
	GameplayTags.Abilities_Passive_LifeSiphon = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Passive.LifeSiphon"), FString("Life Siphon"));
	GameplayTags.Abilities_Passive_ManaSiphon = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Abilities.Passive.ManaSiphon"), FString("Mana Siphon"));

	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"), FString("FireBolt Cooldown Tag"));

	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("CombatSocket.Weapon"), FString("Weapon Socket"));
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("CombatSocket.RightHand"), FString("Right Hand Socket"));
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("CombatSocket.LeftHand"), FString("Left Hand Socket"));
	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("CombatSocket.Tail"), FString("Tail Socket"));

	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Montage.Attack.1"), FString("Attack 1"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Montage.Attack.2"), FString("Attack 2"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Montage.Attack.3"), FString("Attack 3"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Montage.Attack.4"), FString("Attack 4"));

	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Player.Block.InputPressed"), FString("Block Input Pressed callback for input"));
	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Player.Block.InputHeld"), FString("Block Input Held callback for input"));
	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Player.Block.InputReleased"), FString("Block Input Released callback for input"));
	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get()
		.AddNativeGameplayTag(FName("Player.Block.CursorTrace"), FString("Block tracing under the cursor"));
}
