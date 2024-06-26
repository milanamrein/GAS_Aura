// Copyright Milán Amrein


#include "AbilitySystem/Abilities/AuraFireBlast.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AuraGameplayTags.h"
#include "GameFramework/PlayerController.h"
#include "Actor/AuraFireBall.h"

FString UAuraFireBlast::GetDescription(int32 Level)
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
	FString Launch = FString::Printf(TEXT("<Default>Launches %d fire balls in all directions, each coming back and "), NumFireBalls);
	FString LaunchText = Launch.Append(FString::Printf(TEXT("exploding upon return causing </>")));

	// Get & implicitly convert Fire Damage for FireBolt
	const float Damage = GetDamageByType(Level, FAuraGameplayTags::Get().Damage_Fire);
	FString DamageText = FString::Printf(TEXT("<Damage>%.1f</><Default> radial fire damage with a chance to burn.</>"), Damage);

	return FString::Printf(TEXT("<Title>FIRE BLAST</>\n\n"))
		.Append(LevelText)
		.Append(ManaText)
		.Append(CooldownText)
		.Append(LaunchText)
		.Append(DamageText);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 NextLevel)
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
	FString Launch = FString::Printf(TEXT("<Default>Launches %d fire balls in all directions, each coming back and "), NumFireBalls);
	FString LaunchText = Launch.Append(FString::Printf(TEXT("exploding upon return causing </>")));

	// Get & implicitly convert Fire Damage for FireBolt
	const float Damage = GetDamageByType(NextLevel, FAuraGameplayTags::Get().Damage_Fire);
	FString DamageText = FString::Printf(TEXT("<Damage>%.1f</><Default> radial fire damage with a chance to burn.</>"), Damage);

	return FString::Printf(TEXT("<Title>NEXT LEVEL</>\n\n"))
		.Append(LevelText)
		.Append(ManaText)
		.Append(CooldownText)
		.Append(LaunchText)
		.Append(DamageText);
}

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	TArray<AAuraFireBall*> FireBalls;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);
	for (const FRotator& Rotator : Rotators) {
		// Spawn FireBall
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());
		AAuraFireBall* FireBall = GetWorld()->SpawnActorDeferred<AAuraFireBall>(
			FireBallClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		// Set EffectParams on FireBall
		FireBall->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->ReturnToActor = GetAvatarActorFromActorInfo();
		FireBall->ExplosionDamageParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->SetOwner(GetAvatarActorFromActorInfo());

		FireBalls.Add(FireBall);
		FireBall->FinishSpawning(SpawnTransform);
	}

	return FireBalls;
}
