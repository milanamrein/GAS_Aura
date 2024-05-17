// Copyright Milán Amrein


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

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

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	// Spawn replicated Projectile only on server
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	// Spawn Projectile
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag
	);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch) { // Check if we need to override the Pitch (e.g. Projectile is launched in a way that it will hit the ground)
		Rotation.Pitch = PitchOverride;
	}
	
	// Spread out multiple Projectiles
	const FVector Forward = Rotation.Vector();
	NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	TArray<FRotator> Rotations = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);
	for (const FRotator& Rot : Rotations) {
		// Set the Transform to Target
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn // always spawn regardless of collisions or overlaps
		);

		// Give Projectile DamageEffectParams for causing Damage
		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults(); // we don't know the Target Actor yet

		// Homing on the Target
		if (HomingTarget && HomingTarget->Implements<UCombatInterface>()) { // It is an Enemy
			Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
		}
		else { // We hit something static in the World (e.g. floor or wall)
			// Get a Component in the location of our MouseHit
			Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
			Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
			Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;
		}

		// Set Homing acceleration
		Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::FRandRange(HomingAccelerationMin, HomingAccelerationMax);
		Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;

		// Finish spawning Projectile
		Projectile->FinishSpawning(SpawnTransform);
	}
}
