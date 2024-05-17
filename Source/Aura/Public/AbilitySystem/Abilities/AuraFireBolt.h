// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "AuraFireBolt.generated.h"

/**
 * Projectile class for FireBolt
 */
UCLASS()
class AURA_API UAuraFireBolt : public UAuraProjectileSpell
{
	GENERATED_BODY()
	
public:

	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 NextLevel) override;

	/// <summary>
	/// Function to spawn multiple Projectiles when the FireBolt ability has been leveled up
	/// </summary>
	/// <param name="ProjectileTargetLocation">Target location</param>
	/// <param name="SocketTag">Socket Tag to launch the Projectile from</param>
	/// <param name="bOverridePitch">Whether or not to override the Projectile's Pitch Rotation</param>
	/// <param name="PitchOverride">Amount to override the Pitch with</param>
	/// <param name="HomingTarget">Target in case it is an actual Actor (e.g. Enemy)</param>
	UFUNCTION(BlueprintCallable)
	void SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget);


protected:

	/// <summary>
	/// How far to left/right spread the Projectiles
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "FireBolt")
	float ProjectileSpread = 90.f;

	/// <summary>
	/// Maximum number of Projectiles that can be spawned
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "FireBolt")
	int32 MaxNumProjectiles = 5;

	/// <summary>
	/// Minimum speed of FireBolts to turn towards their Target
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "FireBolt")
	float HomingAccelerationMin = 1600.f;

	/// <summary>
	/// Maximum speed of FireBolts to turn towards their Target
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "FireBolt")
	float HomingAccelerationMax = 3200.f;

	/// <summary>
	/// Whether or not this FireBolt is a Homing Projectile
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "FireBolt")
	bool bLaunchHomingProjectiles = true;
};
