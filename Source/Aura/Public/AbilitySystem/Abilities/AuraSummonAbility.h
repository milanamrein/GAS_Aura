// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * Gameplay Ability class for summoning
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Function to calculate summon locations
	/// </summary>
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	/// <summary>
	/// Function to get Minion to Spawn
	/// </summary>
	UFUNCTION(BlueprintPure, Category = "Summoning")
	TSubclassOf<APawn> GetRandomMinionClass();

	/// <summary>
	/// Variable determining the number of Minions to summon
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	int32 NumMinions = 5;

	/// <summary>
	/// Array for the types of Enemies to spawn
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	/// <summary>
	/// Minimum distance away where we should spawn Minions at
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MinSpawnDistance = 50.f;

	/// <summary>
	/// Maximum distance away where we should spawn Minions at
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MaxSpawnDistance = 250.f;

	/// <summary>
	/// Angle of spread for spawning
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float SpawnSpread = 90.f;

};
