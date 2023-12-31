// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MaxHealthMMC.generated.h"

/**
 * Modifier Magnitude Calculation class for MaxHealth Attribute
 */
UCLASS()
class AURA_API UMaxHealthMMC : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMaxHealthMMC();

	// Function that determines the result of the modifier
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	/// <summary>
	/// Variable for capturing Vigor Attribute
	/// </summary>
	FGameplayEffectAttributeCaptureDefinition VigorDef;

};
