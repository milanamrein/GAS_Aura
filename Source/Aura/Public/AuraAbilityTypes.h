#pragma once

#include "GameplayEffectTypes.h"
#include "ScalableFloat.h"
#include "AuraAbilityTypes.generated.h"

class UGameplayEffect;

/// <summary>
/// Struct for storing Damage Effect parameters
/// </summary>
USTRUCT(BlueprintType)
struct FDamageEffectParams 
{
	GENERATED_BODY()

	FDamageEffectParams(){}

	/// <summary>
	/// World Context Object needed for AuraASC Library
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject> WorldContextObject = nullptr;

	/// <summary>
	/// Damage Gameplay Effect Class
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	/// <summary>
	/// Source ASC
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceASC;

	/// <summary>
	/// Target ASC
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> TargetASC;

	/// <summary>
	/// What kind of Damage and how much Damage do we cause
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	TMap<FGameplayTag, float> Damages;

	/// <summary>
	/// Amount of impulse received upon death
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	float DeathImpulseMagnitude = 0.f;

	/// <summary>
	/// Death impulse direction
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FVector DeathImpulse = FVector::ZeroVector;

	/// <summary>
	/// Amount of knockback received upon death
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FScalableFloat KnockbackForceMagnitude = 0.f;

	/// <summary>
	/// Percentage of chance for Knockback
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FScalableFloat KnockbackChance = 0.f;

	/// <summary>
	/// Knockback direction
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FVector KnockbackForce = FVector::ZeroVector;

	/// <summary>
	/// Level of the Ability
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	float AbilityLevel = 1.f;

	/// <summary>
	/// Possibility (percent) of Debuff
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FScalableFloat DebuffChance = 0.f;

	/// <summary>
	/// Amount a Debuff applies while it is active
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FScalableFloat DebuffDamage = 0.f;

	/// <summary>
	/// How frequently apply DebuffDamage in seconds
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FScalableFloat DebuffFrequency = 0.f;

	/// <summary>
	/// Amount of time (seconds) a Debuff is active for
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FScalableFloat DebuffDuration = 0.f;

	/// <summary>
	/// Whether or not the Damage is a radial one
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	bool bIsRadialDamage = false;

	UPROPERTY(BlueprintReadWrite)
	float RadialDamageInnerRadius = 0.f;

	UPROPERTY(BlueprintReadWrite)
	float RadialDamageOuterRadius = 0.f;

	UPROPERTY(BlueprintReadWrite)
	FVector RadialDamageOrigin = FVector::ZeroVector;
};

/// <summary>
/// Struct for Aura ASC's custom GE Context
/// </summary>
USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FGameplayEffectContext* Duplicate() const
	{
		FGameplayEffectContext* NewContext = new FGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Custom serialization used to convert the struct to bits of data so it can be sent across the network */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	/**
	* Getters & Setters
	*/

	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsBlockedHit() const { return bIsBlockedHit; }
	bool IsSuccessfulDebuff() const { return bIsSuccessfulDebuff; }
	float GetDebuffDamage() const { return DebuffDamage; }
	float GetDebuffDuration() const { return DebuffDuration; }
	float GetDebuffFrequency() const { return DebuffFrequency; }
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType; }
	FVector GetDeathImpulse() const { return DeathImpulse; }
	FVector GetKnockbackForce() const { return KnockbackForce; }
	bool IsRadialDamage() const { return bIsRadialDamage; }
	float GetRadialDamageInnerRadius() const { return RadialDamageInnerRadius; }
	float GetRadialDamageOuterRadius() const { return RadialDamageOuterRadius; }
	FVector GetRadialDamageOrigin() const { return RadialDamageOrigin; }

	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsSuccessfulDebuff(bool bInIsSuccessfulDebuff) { bIsSuccessfulDebuff = bInIsSuccessfulDebuff; }
	void SetDebuffDamage(float InDebuffDamage) { DebuffDamage = InDebuffDamage; }
	void SetDebuffDuration(float InDebuffDuration) { DebuffDuration = InDebuffDuration; }
	void SetDebuffFrequency(float InDebuffFrequency) { DebuffFrequency = InDebuffFrequency; }
	void SetDamageType(TSharedPtr<FGameplayTag> InDamageType) { DamageType = InDamageType; }
	void SetDeathImpulse(const FVector& InImpulse) { DeathImpulse = InImpulse; }
	void SetKnockbackForce(const FVector& InForce) { KnockbackForce = InForce; }
	void SetIsRadialDamage(bool InIsRadialDamage) { bIsRadialDamage = InIsRadialDamage; }
	void SetRadialDamageInnerRadius(float InRadialDamageInnerRadius) { RadialDamageInnerRadius = InRadialDamageInnerRadius; }
	void SetRadialDamageOuterRadius(float InRadialDamageOuterRadius) { RadialDamageOuterRadius = InRadialDamageOuterRadius; }
	void SetRadialDamageOrigin(const FVector& InRadialDamageOrigin) { RadialDamageOrigin = InRadialDamageOrigin; }

protected:

	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;

	UPROPERTY()
	bool bIsSuccessfulDebuff = false;

	UPROPERTY()
	float DebuffDamage = 0.f;

	UPROPERTY()
	float DebuffDuration = 0.f;

	UPROPERTY()
	float DebuffFrequency = 0.f;

	TSharedPtr<FGameplayTag> DamageType;

	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;

	UPROPERTY()
	FVector KnockbackForce = FVector::ZeroVector;

	UPROPERTY()
	bool bIsRadialDamage = false;

	UPROPERTY()
	float RadialDamageInnerRadius = 0.f;

	UPROPERTY()
	float RadialDamageOuterRadius = 0.f;

	UPROPERTY()
	FVector RadialDamageOrigin = FVector::ZeroVector;
};

// Template needed to define our custom GameplayEffectContext
template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};