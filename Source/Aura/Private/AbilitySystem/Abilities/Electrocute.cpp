// Copyright Milán Amrein


#include "AbilitySystem/Abilities/Electrocute.h"
#include "AuraGameplayTags.h"

FString UElectrocute::GetDescription(int32 Level)
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
	FString Launch = Level == 1 ? FString::Printf(TEXT("<Default>Emmits a beam of lightning "))
		: FString::Printf(TEXT("<Default>Emmits %d beams of lightning "), FMath::Min(Level, MaxTargets));
	FString LaunchText = Launch.Append(FString::Printf(TEXT("connecting with the target, repeatedly causing </>")));

	// Get & implicitly convert Lightning Damage for Electrocute
	const float Damage = GetDamageByType(Level, FAuraGameplayTags::Get().Damage_Lightning);
	FString DamageText = FString::Printf(TEXT("<Damage>%.1f</><Default> lightning damage with a chance to stun.</>"), Damage);

	return FString::Printf(TEXT("<Title>ELECTROCUTE</>\n\n"))
		.Append(LevelText)
		.Append(ManaText)
		.Append(CooldownText)
		.Append(LaunchText)
		.Append(DamageText);
}

FString UElectrocute::GetNextLevelDescription(int32 NextLevel)
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
	FString LaunchText = FString::Printf(TEXT("<Default>Emmits %d beams of lightning, connecting with the target, repeatedly causing </>"), FMath::Min(NextLevel, MaxTargets));

	// Get & implicitly convert Lightning Damage for Electrocute
	const float Damage = GetDamageByType(NextLevel, FAuraGameplayTags::Get().Damage_Lightning);
	FString DamageText = FString::Printf(TEXT("<Damage>%.1f</><Default> lightning damage with a chance to stun.</>"), Damage);

	return FString::Printf(TEXT("<Title>NEXT LEVEL</>\n\n"))
		.Append(LevelText)
		.Append(ManaText)
		.Append(CooldownText)
		.Append(LaunchText)
		.Append(DamageText);
}
