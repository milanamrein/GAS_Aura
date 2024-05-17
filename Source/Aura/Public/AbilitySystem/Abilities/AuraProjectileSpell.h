// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;
struct FGameplayTag;

/**
 * Gameplay Ability class for Projectiles
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	/// <summary>
	/// Function to spawn a Projectile from BP when the corresponding
	/// Event is triggered
	/// </summary>
	/// <param name="ProjectileTargetLocation">Target location</param>
	/// <param name="SocketTag">Socket Tag to launch the Projectile from</param>
	/// <param name="bOverridePitch">Whether or not to override the Projectile's Pitch Rotation</param>
	/// <param name="PitchOverride">Amount to override the Pitch with</param>
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch = false, float PitchOverride = 0.f);

	/// <summary>
	/// Class to spawn a Projectile from
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;

	/// <summary>
	/// Number of projectiles that can be fired at once
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	int32 NumProjectiles = 5;
};
