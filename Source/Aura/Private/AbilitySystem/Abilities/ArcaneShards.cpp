// Copyright Milán Amrein


#include "AbilitySystem/Abilities/ArcaneShards.h"
#include "AuraGameplayTags.h"

FString UArcaneShards::GetDescription(int32 Level)
{
	// Level
	FString LevelText = FString::Printf(TEXT("<Small>Level: </><Level>%d</>\n"), Level);

	// Cost
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	FString ManaText = FString::Printf(TEXT("<Small>ManaCost: </><ManaCost>%.1f</>\n"), ManaCost);

	// Cooldown
	const float Cooldown = GetCooldown(Level);
	FString CooldownText = FString::Printf(TEXT("<Small>Cooldown: </><Cooldown>%.1f</>\n\n"), Cooldown);

	// Description
	FString Launch = Level == 1 ? FString::Printf(TEXT("<Default>Summon a shard of arcane energy "))
		: FString::Printf(TEXT("<Default>Summon %d shards of arcane energy "), FMath::Min(Level, MaxNumShards));
	FString LaunchText = Launch.Append(FString::Printf(TEXT("causing radial damage of </>")));

	// Get & implicitly convert Arcane Damage for Arcane Shards
	const float Damage = GetDamageByType(Level, FAuraGameplayTags::Get().Damage_Arcane);
	FString DamageText = FString::Printf(TEXT("<Damage>%.1f</><Default> at the shard origin.</>"), Damage);

	return FString::Printf(TEXT("<Title>ARCANE SHARDS</>\n\n"))
		.Append(LevelText)
		.Append(ManaText)
		.Append(CooldownText)
		.Append(LaunchText)
		.Append(DamageText);
}

FString UArcaneShards::GetNextLevelDescription(int32 NextLevel)
{
	// Level
	FString LevelText = FString::Printf(TEXT("<Small>Level: </><Level>%d</>\n"), NextLevel);

	// Cost
	const float ManaCost = FMath::Abs(GetManaCost(NextLevel));
	FString ManaText = FString::Printf(TEXT("<Small>ManaCost: </><ManaCost>%.1f</>\n"), ManaCost);

	// Cooldown
	const float Cooldown = GetCooldown(NextLevel);
	FString CooldownText = FString::Printf(TEXT("<Small>Cooldown: </><Cooldown>%.1f</>\n\n"), Cooldown);

	// Description
	FString LaunchText = FString::Printf(TEXT("<Default>Summon %d shards of arcane energy causing radial damage of </>"), FMath::Min(NextLevel, MaxNumShards));

	// Get & implicitly convert Arcane Damage for Arcane Shards
	const float Damage = GetDamageByType(NextLevel, FAuraGameplayTags::Get().Damage_Arcane);
	FString DamageText = FString::Printf(TEXT("<Damage>%.1f</><Default> at the shard origin.</>"), Damage);

	return FString::Printf(TEXT("<Title>NEXT LEVEL</>\n\n"))
		.Append(LevelText)
		.Append(ManaText)
		.Append(CooldownText)
		.Append(LaunchText)
		.Append(DamageText);
}
