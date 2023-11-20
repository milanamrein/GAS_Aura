// Copyright Milán Amrein


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Interaction/CombatInterface.h"
#include "Actor/AuraProjectile.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	// Spawn replicated Projectile only on server
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	if (ICombatInterface* CombatActor = Cast<ICombatInterface>(GetAvatarActorFromActorInfo())) {
		// Spawn Projectile
		const FVector SocketLocation = CombatActor->GetCombatSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

		// Set the Transform to Target
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		//SpawnActorDeferred() allows us to set GameplayEffects and other properties on the Actor before spawning it
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass, 
			SpawnTransform, 
			GetOwningActorFromActorInfo(), 
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn // always spawn regardless of collisions or overlaps
			);

		// Give Projectile a Gameplay Effect Spec and Context Handle for causing Damage
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(Projectile);
		EffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		HitResult.Location = ProjectileTargetLocation;
		EffectContextHandle.AddHitResult(HitResult);
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

		// Get ScaledDamage for each Damage type
		FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		for (auto& Pair : DamageTypes) {
			// Set by Caller so this Gameplay Ability has control over how much Damage is done by the Projectile Actor
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
				SpecHandle, 
				Pair.Key, // Gameplay Tag, Damage Type
				Pair.Value.GetValueAtLevel(GetAbilityLevel()) // ScaledDamage value for Damage Type
			);
		}

		// Set Projectile's GE
		Projectile->DamageEffectSpecHandle = SpecHandle;

		// Finish spawning Projectile
		Projectile->FinishSpawning(SpawnTransform);
	}

}
