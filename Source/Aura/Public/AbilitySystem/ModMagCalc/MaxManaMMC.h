// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MaxManaMMC.generated.h"

/**
 * Modifier Magnitude Calculation class for MaxMana Attribute
 */
UCLASS()
class AURA_API UMaxManaMMC : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMaxManaMMC();

	// Function that determines the result of the modifier
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	/// <summary>
	/// Variable for capturing Intelligence Attribute
	/// </summary>
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;

};
