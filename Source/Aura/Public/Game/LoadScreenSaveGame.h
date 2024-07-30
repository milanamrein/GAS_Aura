// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"

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

	/**
	* Saved Game Data
	*/

	UPROPERTY()
	FString PlayerName = FString("Default Name");

	UPROPERTY()
	FString MapName = FString("Default Map Name");
};
