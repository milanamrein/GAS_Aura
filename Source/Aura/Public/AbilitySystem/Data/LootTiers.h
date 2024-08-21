// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LootTiers.generated.h"

USTRUCT(BlueprintType)
struct FLootItem
{
	GENERATED_BODY()

	/// <summary>
	/// Loot class to spawn
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LootTiers|Spawning")
	TSubclassOf<AActor> LootClass;

	/// <summary>
	/// Chance of this Item being spawned
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "LootTiers|Spawning")
	float Chance = 0.f;

	/// <summary>
	/// Maximum number of Items to spawn
	/// from this type of Loot
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "LootTiers|Spawning")
	int32 MaxNum = 1;

	/// <summary>
	/// If true, override the level of this Loot
	/// to the level of the Enemy spawning it
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LootTiers|Spawning")
	bool bLootLevelOverride = true;
};

/**
 * Data Asset class for storing Loots 
 * with different Tiers of Level
 */
UCLASS()
class AURA_API ULootTiers : public UDataAsset
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Function to handle getting all the Loot Items
	/// the game is about to spawn
	/// </summary>
	UFUNCTION(BlueprintCallable)
	TArray<FLootItem> GetLootItems();

	UPROPERTY(EditDefaultsOnly, Category = "LootTiers|Spawning")
	TArray<FLootItem> LootItems;
};
