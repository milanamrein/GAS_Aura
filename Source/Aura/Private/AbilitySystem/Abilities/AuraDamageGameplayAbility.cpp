// Copyright Milán Amrein


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	// Assign Tag Magnitudes
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);
	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes) {
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaledDamage);
	}

	// Apply Ability to Target
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*DamageSpecHandle.Data.Get(), 
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor)
	);
}

FDamageEffectParams UAuraDamageGameplayAbility::MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor, FVector InRadialDamageOrigin, bool bOverrideKnockbackDirection, FVector InKnockbackDirectionOverride, bool bOverrideDeathImpulse, FVector InDeathImpulseDirectionOverride, bool bOverridePitch, float InPitchOverride) const
{
	FDamageEffectParams Params;
	Params.WorldContextObject = GetAvatarActorFromActorInfo();
	Params.DamageGameplayEffectClass = DamageEffectClass;
	Params.SourceASC = GetAbilitySystemComponentFromActorInfo();
	Params.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor); // Library function checks if Actor is null
	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes) {
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		Params.Damages.Add(Pair.Key, ScaledDamage);
	}
	Params.AbilityLevel = GetAbilityLevel();
	Params.DebuffChance = DebuffChance;
	Params.DebuffDamage = DebuffDamage;
	Params.DebuffDuration = DebuffDuration;
	Params.DebuffFrequency = DebuffFrequency;
	Params.DeathImpulseMagnitude = DeathImpulseMagnitude;
	Params.KnockbackForceMagnitude = KnockbackForceMagnitude;
	Params.KnockbackChance = KnockbackChance;

	// Set default Pitch Rotation for Knockback and Death Impulse
	FRotator Rotation = FRotator::ZeroRotator;
	FVector ToTarget = FVector::ZeroVector;
	if (IsValid(TargetActor)) {
		Rotation = (TargetActor->GetActorLocation() - GetAvatarActorFromActorInfo()->GetActorLocation()).Rotation();
		Rotation.Pitch = 45.f;
		ToTarget = Rotation.Vector();
	}

	// If Knockback override is true, set Knockback Force to Kockback override
	if (bOverrideKnockbackDirection) {
		InKnockbackDirectionOverride.Normalize();
		Params.KnockbackForce = InKnockbackDirectionOverride * KnockbackForceMagnitude.GetValueAtLevel(GetAbilityLevel());
		if (bOverridePitch) {
			Rotation = InKnockbackDirectionOverride.Rotation();
			Rotation.Pitch = InPitchOverride;
			ToTarget = Rotation.Vector();
			Params.KnockbackForce = ToTarget * KnockbackForceMagnitude.GetValueAtLevel(GetAbilityLevel());
		}
	}
	else if (!ToTarget.IsZero()) { // If Knockback override is false and Target is valid, calculate direction of knockback from AvatarActor to Target
		Params.KnockbackForce = ToTarget * KnockbackForceMagnitude.GetValueAtLevel(GetAbilityLevel());
	}

	// If Death Impulse override is true, override Death Impulse
	if (bOverrideDeathImpulse) {
		InDeathImpulseDirectionOverride.Normalize();
		Params.DeathImpulse = InDeathImpulseDirectionOverride * DeathImpulseMagnitude;
		if (bOverridePitch) {
			Rotation = InDeathImpulseDirectionOverride.Rotation();
			Rotation.Pitch = InPitchOverride;
			ToTarget = Rotation.Vector();
			Params.DeathImpulse = ToTarget * DeathImpulseMagnitude;
		}
	}
	else if (!ToTarget.IsZero()) { // If Death Impulse override is false and Target is valid, calculate direction of death impulse from AvatarActor to Target
		Params.DeathImpulse = ToTarget * DeathImpulseMagnitude;
	}

	// Apply Radial Damage EffectParams if this Damage Ability is Radial Damage
	if (bIsRadialDamage) {
		Params.bIsRadialDamage = bIsRadialDamage;
		Params.RadialDamageOrigin = InRadialDamageOrigin; // InRadialDamageOrigin can't be a reference because this function's usage in BP
		Params.RadialDamageInnerRadius = RadialDamageInnerRadius;
		Params.RadialDamageOuterRadius = RadialDamageOuterRadius;
	}

	return Params;
}

float UAuraDamageGameplayAbility::GetDamageAtLevel(const FGameplayTag& DamageTag) const
{
	return DamageTypes.Find(DamageTag)->GetValueAtLevel(GetAbilityLevel());
}

FTaggedMontage UAuraDamageGameplayAbility::GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const
{
	if (TaggedMontages.Num() > 0) { // array is not empty
		const int32 Selection = FMath::RandRange(0, TaggedMontages.Num() - 1);
		return TaggedMontages[Selection];
	}

	return FTaggedMontage();
}

float UAuraDamageGameplayAbility::GetDamageByType(float InLevel, const FGameplayTag& DamageType)
{
	checkf(DamageTypes.Contains(DamageType), TEXT("GameplayAbility [%s] does not contain DamageType [%s]"), *GetNameSafe(this), *DamageType.ToString());

	return DamageTypes[DamageType].GetValueAtLevel(InLevel);
}
