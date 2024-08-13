// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"

class UGameplayAbility;

/**
 * Enum for Slot Statuses
 */
UENUM(BlueprintType)
enum ESaveSlotStatus 
{
	Vacant,
	EnterName,
	Taken
};

/**
* Struct to store a saved Actor's data
*/
USTRUCT(BlueprintType)
struct FSavedActor
{
	GENERATED_BODY()

	/// <summary>
	/// Actor's Name
	/// </summary>
	UPROPERTY()
	FName ActorName = FName();

	/// <summary>
	/// Actor's location on the Map/Level
	/// </summary>
	UPROPERTY()
	FTransform ActorTransform = FTransform();

	/// <summary>
	/// Serialized variables from the Actor 
	/// (class members marked with SaveGame specifier)
	/// </summary>
	UPROPERTY()
	TArray<uint8> Bytes;
};

// Overload == to add serialized variables to Bytes array
inline bool operator==(const FSavedActor& Left, const FSavedActor& Right)
{
	return Left.ActorName.IsEqual(Right.ActorName);
}

/**
* Struct to store a Map's saved data
*/
USTRUCT(BlueprintType)
struct FSavedMap
{
	GENERATED_BODY()

	/// <summary>
	/// Map Asset's Name
	/// </summary>
	UPROPERTY()
	FString MapAssetName = FString();

	/// <summary>
	/// Array of FSavedActors that are
	/// on this Map
	/// </summary>
	UPROPERTY()
	TArray<FSavedActor> SavedActors;
};

/**
* Struct to store a saved Ability's data
*/
USTRUCT(BlueprintType)
struct FSavedAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayAbility> GameplayAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityStatus = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityInput = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityType = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AbilityLevel = 1;
};

// Overload == to add unique FSavedAbility to SavedAbilities map
inline bool operator==(const FSavedAbility& Left, const FSavedAbility& Right)
{
	return Left.AbilityTag.MatchesTagExact(Right.AbilityTag);
}

/**
 * Class to save data from the Load Screen
 */
UCLASS()
class AURA_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Saved Slot's Name provided in the input
	/// which uniquely identifies the Slot
	/// </summary>
	UPROPERTY()
	FString SlotName = FString();

	/// <summary>
	/// Slot's Index in the Switcher
	/// </summary>
	UPROPERTY()
	int32 SlotIndex = 0;

	/// <summary>
	/// Status of the Slot
	/// </summary>
	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = Vacant;

	/// <summary>
	/// It is true if we don't have any saved data in SaveObject -> load initial data
	/// It is false if we already have saved data -> load data from disk
	/// </summary>
	UPROPERTY()
	bool bFirstTimeLoadIn = true;

	/**
	* Saved Game Data
	*/

	UPROPERTY()
	FString PlayerName = FString("Default Name");

	UPROPERTY()
	FString MapName = FString("Default Map Name");

	/// <summary>
	/// Tag of the PlayerStart the Player should start at
	/// </summary>
	UPROPERTY()
	FName PlayerStartTag;

	/**
	* Player
	*/

	UPROPERTY()
	int32 PlayerLevel = 1;

	UPROPERTY()
	int32 XP = 0;

	UPROPERTY()
	int32 SpellPoints = 0;

	UPROPERTY()
	int32 AttributePoints = 0;

	/**
	* Attributes
	* - Only Primary ones are needed to be saved as all the others are derived from these
	*/

	UPROPERTY()
	float Strength = 0;

	UPROPERTY()
	float Intelligence = 0;

	UPROPERTY()
	float Resilience = 0;

	UPROPERTY()
	float Vigor = 0;

	/**
	* Abilities
	*/

	UPROPERTY()
	TArray<FSavedAbility> SavedAbilities;

	/**
	* Maps
	*/

	UPROPERTY()
	TArray<FSavedMap> SavedMaps;

	/// <summary>
	/// Function to return a specific saved Map based on its name
	/// </summary>
	FSavedMap GetSavedMap(const FString& InMapName);

	/// <summary>
	/// Function to check if SavedMaps has a Map with the given MapName
	/// </summary>
	bool HasMap(const FString& InMapName);
};
