// Copyright Milán Amrein


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Interaction/CombatInterface.h"
#include "Actor/AuraProjectile.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// spawn replicated Projectile only on server
	if (!HasAuthority(&ActivationInfo)) return;

	if (ICombatInterface* CombatActor = Cast<ICombatInterface>(GetAvatarActorFromActorInfo())) {
		// Spawn Projectile
		const FVector SocketLocation = CombatActor->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		// TODO: Set the Projectile Rotation

		//SpawnActorDeferred() allows us to set GameplayEffects and other properties on the Actor before spawning it
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass, 
			SpawnTransform, 
			GetOwningActorFromActorInfo(), 
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn // always spawn regardless of collisions or overlaps
			);

		// TODO: Give Projectile a Gameplay Effect Spec for causing Damage

		// Finish spawning Projectile
		Projectile->FinishSpawning(SpawnTransform);
	}
}
