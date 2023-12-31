// Copyright Milán Amrein


#include "AbilitySystem/ModMagCalc/MaxHealthMMC.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMaxHealthMMC::UMaxHealthMMC()
{
	// Configure Vigor for Capture
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute(); // can be used due to GAMEPLAYATTRIBUTE_PROPERTY_GETTER in AuraAttributeSet.h
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false; // getting the value of the effect at the time of applying the effect

	// Add Vigor to MMC's AttributesToCapture array
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMaxHealthMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Capture Vigor
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	float Vigor = 0.f; // this variable will hold the captured value of Vigor Attribute on the Target set in GetCapturedAttributeMagnitude
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f); // make Vigor a non-negative float

	// Get Character's Level
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetCharacterLevel();

	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
