// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

/**
* Struct with information on each Level
*/
USTRUCT(BlueprintType)
struct FAuraLevelUpInfo {
	GENERATED_BODY();

	/// <summary>
	/// Amount of XP required in order to level-up
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpRequirement = 0;

	/// <summary>
	/// Amount of Attribute Points rewarded for leveling up to this Level
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointReward = 1;

	/// <summary>
	/// Amount of Spell Points rewarded for leveling up to this Level
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	int32 SpellPointReward = 1;
};

/**
 * Data Asset class to store information about Levels
 */
UCLASS()
class AURA_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraLevelUpInfo> LevelUpInformation;

	/// <summary>
	/// Function to find the Level for a given amount of XP
	/// </summary>
	int32 FindLevelForXP(int32 XP) const;
};
