// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class UAnimMontage;

/**
 * Interface for Combat interaction
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Function to return a Character's Level
	/// </summary>
	/// <returns>Level</returns>
	virtual int32 GetCharacterLevel();

	/// <summary>
	/// Function to return a Socket location for spawning Spells
	/// </summary>
	/// <returns>Combat Socket's location</returns>
	virtual FVector GetCombatSocketLocation();
	
	/// <summary>
	/// Function to update the Facing Target during Motion Warping
	/// </summary>
	/// <param name="Target">Target to rotate towards</param>
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent) // BlueprintImplementableEvent cannot be virtual
	void UpdateFacingTarget(const FVector& Target);

	/// <summary>
	/// Function to get the Montage when the
	/// Combat Actor is being hit
	/// </summary>
	/// <returns>HitReact Animation Montage</returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) // don't need to be virtual to be overridden in C++ and be callable in BP
	UAnimMontage* GetHitReactMontage();

	/// <summary>
	/// Function to when a Combat Actor dies
	/// </summary>
	virtual void Die() = 0;
};
