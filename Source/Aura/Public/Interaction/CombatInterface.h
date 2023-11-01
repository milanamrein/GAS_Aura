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
};
