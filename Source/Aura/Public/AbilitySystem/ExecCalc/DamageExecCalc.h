// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecCalc.generated.h"

/**
 * Execution Calculation class for Damage.
 * Belongs to a Gameplay Effect.
 */
UCLASS()
class AURA_API UDamageExecCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:

	UDamageExecCalc();

	/** Function to decide how this ExecCalc is going to affect any other Attributes by setting their values. */
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
