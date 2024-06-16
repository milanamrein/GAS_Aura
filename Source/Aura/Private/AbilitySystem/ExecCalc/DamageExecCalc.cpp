// Copyright Milán Amrein


#include "AbilitySystem/ExecCalc/DamageExecCalc.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AuraGameplayTags.h"
#include "Interaction/CombatInterface.h"
#include "AuraAbilityTypes.h"
#include "Kismet/GameplayStatics.h"

/// <summary>
/// Raw struct to hold all of the
/// CaptureDefinitions
/// </summary>
struct AuraDamageStatics
{
	// Declare CaptureDefinitions macro
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor); // we can put anything as a name arg
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	AuraDamageStatics()
	{
		// macro to define CaptureDefinitions
		// AttributeSet, AttributeToCapture, AttributeSource, whether or not to snapshot
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false); // used by Attacker, not Target
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PhysicalResistance, Target, false);
	}
};

// Function to return the one and only AuraDamageStatics struct
static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics; // has static storage duration, exists even after the function ends
	
	return DStatics;
}

UDamageExecCalc::UDamageExecCalc()
{
	// Define Attributes that should be affected by this ExecCalc
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);

}

void UDamageExecCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// TMap mapping Capture Defs to their corresponding Attribute Tags
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCapture;

	TagsToCapture.Add(FAuraGameplayTags::Get().Attributes_Secondary_Armor, DamageStatics().ArmorDef);
	TagsToCapture.Add(FAuraGameplayTags::Get().Attributes_Secondary_ArmorPenetration, DamageStatics().ArmorPenetrationDef);
	TagsToCapture.Add(FAuraGameplayTags::Get().Attributes_Secondary_BlockChance, DamageStatics().BlockChanceDef);
	TagsToCapture.Add(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitChance, DamageStatics().CriticalHitChanceDef);
	TagsToCapture.Add(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitResistance, DamageStatics().CriticalHitResistanceDef);
	TagsToCapture.Add(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitDamage, DamageStatics().CriticalHitDamageDef);

	TagsToCapture.Add(FAuraGameplayTags::Get().Attributes_Resistance_Fire, DamageStatics().FireResistanceDef);
	TagsToCapture.Add(FAuraGameplayTags::Get().Attributes_Resistance_Lightning, DamageStatics().LightningResistanceDef);
	TagsToCapture.Add(FAuraGameplayTags::Get().Attributes_Resistance_Arcane, DamageStatics().ArcaneResistanceDef);
	TagsToCapture.Add(FAuraGameplayTags::Get().Attributes_Resistance_Physical, DamageStatics().PhysicalResistanceDef);

	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	int32 SourcePlayerLevel = 1;
	if (SourceAvatar->Implements<UCombatInterface>()) {
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	int32 TargetPlayerLevel = 1;
	if (TargetAvatar->Implements<UCombatInterface>()) {
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle Context = Spec.GetContext();

	// Capture Armor Definition
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	// Determining Debuffs
	DetermineDebuff(Spec, ExecutionParams, EvaluationParameters, TagsToCapture);

	// Get Damage Set by Caller magnitude for all Damage types
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	float Damage = 0.f;
	for (const auto& Pair : GameplayTags.DamageTypesToResistances) {
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		// check if Tag exists in TagsToCapture map
		checkf(TagsToCapture.Contains(ResistanceTag), TEXT("TagsToCaptureDefs does not contain Tag: [%s] in DamageExecCalc"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCapture[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag, false); // if Damage Type Tag not found, it will be 0.f
		if (DamageTypeValue <= 0.f) { // if there is no Damage Value, continue iteration
			continue;
		}

		// Capture Resistance value based on CaptureDef
		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f); // should be between 0 and 100

		DamageTypeValue *= (100.f - Resistance) / 100.f; // if Resistance is e.g. 90%, then reduce Damage by 90%

		// Apply Radial Damage
		if (UAuraAbilitySystemLibrary::IsRadialDamage(Context)) {
			if (ICombatInterface* CombatActor = Cast<ICombatInterface>(TargetAvatar)) {
				CombatActor->GetOnDamageDelegate().AddLambda([&](float DamageAmount) {
					DamageTypeValue = DamageAmount;
				});
			}

			UGameplayStatics::ApplyRadialDamageWithFalloff(
				TargetAvatar,
				DamageTypeValue,
				0.f,
				UAuraAbilitySystemLibrary::GetRadialDamageOrigin(Context),
				UAuraAbilitySystemLibrary::GetRadialDamageInnerRadius(Context),
				UAuraAbilitySystemLibrary::GetRadialDamageOuterRadius(Context),
				1.f,
				UDamageType::StaticClass(),
				TArray<AActor*>(),
				SourceAvatar,
				nullptr
			);
		}

		Damage += DamageTypeValue;
	}

	// Capture Block Chance on Target
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(0.f, TargetBlockChance); // making sure it is not negative
	
	// BlockChance is a chance, so e.g. if it is 25%, then block will be successful if the random number is less than 26
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	UAuraAbilitySystemLibrary::SetIsBlockedHit(Context, bBlocked);

	// Determine if there was a successful Block. If Block, halve the damage.
	Damage = bBlocked ? Damage / 2.f : Damage;

	// Capture Armor on Target
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(0.f, TargetArmor); // making sure it is not negative

	// Capture Armor Penetration on Source
	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(0.f, SourceArmorPenetration); // making sure it is not negative

	// Get Coefficient for ArmorPenetration
	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel);

	// Armor Penetration ignores a percentage of Target's Armor
	// If e.g. SourceArmorPenetration is 400 and coefficient is .25f, then EffectiveArmor is 0, meaning the Attacker can ignore all of Target's Armor.
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;

	// Get Coefficient for EffectiveArmor
	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel);

	// It would take EffectiveArmorCoefficient points of EffectiveArmor to ignore 1% of the Damage
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;

	// Capturing Critical Hit
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(0.f, SourceCriticalHitChance);

	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaluationParameters, TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(0.f, TargetCriticalHitResistance);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluationParameters, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(0.f, SourceCriticalHitDamage);

	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"), FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(TargetPlayerLevel);

	// CriticalHitResistance reduces CriticalHitChance by a certain percentage, which is a chance like BlockChance
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;
	UAuraAbilitySystemLibrary::SetIsCriticalHit(Context, bCriticalHit);

	// If CriticalHitChance results in a Critical Hit, double Damage plus a bonus
	Damage = bCriticalHit ? 2.f * Damage + SourceCriticalHitDamage : Damage;

	// Modify Attributes
	const FGameplayModifierEvaluatedData EvaluatedData(
		UAuraAttributeSet::GetIncomingDamageAttribute(), // Attribute to modify
		EGameplayModOp::Additive, // Modifier operation
		Damage // Magnitude
	);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

void UDamageExecCalc::DetermineDebuff(const FGameplayEffectSpec& Spec, const FGameplayEffectCustomExecutionParameters& ExecutionParams, FAggregatorEvaluateParameters& EvaluationParameters, const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs) const
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	for (TTuple<FGameplayTag, FGameplayTag> Pair : GameplayTags.DamageTypesToDebuffs) {
		// Get Magnitude based on DamageType; default to -1 if Damage Type not found
		const FGameplayTag& DamageType = Pair.Key;
		const FGameplayTag& DebuffType = Pair.Value;
		const float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);
		// We don't apply negative Damage
		if (TypeDamage > -.5f) { // .5 padding for floating point [im]precision
			// Determine if there was a successful Debuff 
			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Info_Chance, false, -1.f);
			// Get Target's Resistance to Debuff
			float TargetDebuffResistance = 0.f;
			const FGameplayTag& ResistanceTag = GameplayTags.DamageTypesToResistances[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
				InTagsToDefs[ResistanceTag],
				EvaluationParameters,
				TargetDebuffResistance
			);
			TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.f);

			// Calculate Effective Debuff Chance - if SourceDebuffChance and TargetDebuffResistance are 20, then Effective Debuff Chance is 16%
			const float EffectiveDebuffChance = SourceDebuffChance * (100 - TargetDebuffResistance) / 100.f;
			const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance; // Did we get a Debuff?
			if (bDebuff) { // Successful Debuff
				FGameplayEffectContextHandle ContextHandle = Spec.GetContext();
				UAuraAbilitySystemLibrary::SetIsSuccessfulDebuff(ContextHandle, true);
				UAuraAbilitySystemLibrary::SetDamageType(ContextHandle, DamageType);

				// We set the Debuffs by caller magnitude using UAuraAbilitySystemLibrary::ApplyDamageEffect in AuraProjectile
				const float DebuffDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Info_Damage, false, -1.f);
				const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Info_Duration, false, -1.f);
				const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Info_Frequency, false, -1.f);

				// Set Debuffs
				UAuraAbilitySystemLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
				UAuraAbilitySystemLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
				UAuraAbilitySystemLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);
			}
		}
	}
}
