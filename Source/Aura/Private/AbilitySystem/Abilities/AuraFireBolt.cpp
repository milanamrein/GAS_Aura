// Copyright Milán Amrein


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
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
	FString Launch = Level == 1 ? FString::Printf(TEXT("<Default>Launches a bolt ")) 
		: FString::Printf(TEXT("<Default>Launches %d bolts "), FMath::Min(Level, NumProjectiles));
	FString LaunchText = Launch.Append(FString::Printf(TEXT("of fire, exploding impact and dealing: </>")));

	// Get & implicitly convert Fire Damage for FireBolt
	const int32 Damage = GetDamageByType(Level, FAuraGameplayTags::Get().Damage_Fire);
	FString DamageText = FString::Printf(TEXT("<Damage>%d</><Default> fire damage with a chance to burn</>"), Damage);

	return FString::Printf(TEXT("<Title>FIRE BOLT</>\n\n"))
		.Append(LevelText)
		.Append(ManaText)
		.Append(CooldownText)
		.Append(LaunchText)
		.Append(DamageText);
}

FString UAuraFireBolt::GetNextLevelDescription(int32 NextLevel)
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
	FString LaunchText = FString::Printf(TEXT("<Default>Launches %d bolts of fire, exploding impact and dealing: </>"), FMath::Min(NextLevel, NumProjectiles));

	// Get & implicitly convert Fire Damage for FireBolt
	const int32 Damage = GetDamageByType(NextLevel, FAuraGameplayTags::Get().Damage_Fire);
	FString DamageText = FString::Printf(TEXT("<Damage>%d</><Default> fire damage with a chance to burn</>"), Damage);

	return FString::Printf(TEXT("<Title>NEXT LEVEL</>\n\n"))
		.Append(LevelText)
		.Append(ManaText)
		.Append(CooldownText)
		.Append(LaunchText)
		.Append(DamageText);
}