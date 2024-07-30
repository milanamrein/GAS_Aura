// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UCharacterClassInfo;
class UAbilityInfo;
class ULoadSlotViewModel;
class USaveGame;
class ULoadScreenSaveGame;

/**
 * Aura GameModeBase class
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Character Class Data Asset
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	/// <summary>
	/// Player's AbilityInfo Data Asset
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Ability Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;
	
	/// <summary>
	/// Function to save game data to disk
	/// </summary>
	/// <param name="LoadSlot">Load Slot pointer to save data</param>
	/// <param name="SlotIndex">Load Slot's Index</param>
	void SaveSlotData(ULoadSlotViewModel* LoadSlot, int32 SlotIndex);

	/// <summary>
	/// Function to get a SaveGame object from a Load Slot
	/// </summary>
	/// <param name="SlotName">Load Slot Name</param>
	/// <param name="SlotIndex">Load Slot Index</param>
	/// <returns>SaveGame object</returns>
	ULoadScreenSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const;

	/// <summary>
	/// Static function to delete a Load Slot
	/// </summary>
	static void DeleteSlot(const FString& SlotName, int32 SlotIndex);

	/// <summary>
	/// Function to travel to a Level/Map
	/// </summary>
	/// <param name="Slot">Slot to load the Map/Level from</param>
	void TravelToMap(ULoadSlotViewModel* Slot);

protected:

	virtual void BeginPlay() override;

	/// <summary>
	/// Name of the starting Level/Map
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	FString DefaultMapName;

	/// <summary>
	/// Pointer to the starting Level/Map
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefaultMap;

	/// <summary>
	/// Map of all the Levels associated with their names
	/// as keys
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;

private:

	/// <summary>
	/// Class of the object to save the game from the Load Screen
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;

public:

	FString GetDefaultMapName() const { return DefaultMapName; }
};
