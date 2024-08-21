// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UCharacterClassInfo;
class UAbilityInfo;
class ULootTiers;
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
	/// Loot Tiers Data Asset
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Loot Tiers")
	TObjectPtr<ULootTiers> LootTiers;
	
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
	/// Function to get the current SaveGame object
	/// </summary>
	/// <returns>SaveGame object</returns>
	ULoadScreenSaveGame* GetInGameSaveData() const;

	/// <summary>
	/// Function to save the in-game progress
	/// </summary>
	/// <param name="SaveObject">Object holding new save game data</param>
	void SaveInGameProgress(ULoadScreenSaveGame* SaveObject);

	/// <summary>
	/// Function to save the current state of
	/// the World
	/// </summary>
	/// <param name="World">Pointer to the World the Player is in at the time of saving</param>
	/// <param name="DestinationMapAssetName">Name of the Destination Map Asset</param>
	void SaveWorldState(UWorld* World, const FString& DestinationMapAssetName = FString()) const;

	/// <summary>
	/// Function to load the current state of
	/// the World
	/// </summary>
	/// <param name="World">Pointer to the World the Player was in at the time of saving</param>
	void LoadWorldState(UWorld* World) const;

	/// <summary>
	/// Static function to delete a Load Slot
	/// </summary>
	static void DeleteSlot(const FString& SlotName, int32 SlotIndex);

	/// <summary>
	/// Function to travel to a Level/Map
	/// </summary>
	/// <param name="Slot">Slot to load the Map/Level from</param>
	void TravelToMap(ULoadSlotViewModel* Slot);

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	/// <summary>
	/// Callback function to when the Player Character has died
	/// </summary>
	/// <param name="DeadCharacter">Pointer to the dead Character</param>
	void PlayerDied(ACharacter* DeadCharacter);

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
	/// Tag of the default PlayerStart
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStartTag;

	/// <summary>
	/// Map of all the Levels associated with their names
	/// as keys
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;

	/// <summary>
	/// Gets the actual name of a specific Map based
	/// on its Asset Name
	/// </summary>
	FString GetMapNameFromMapAssetName(const FString& InMapAssetName) const;

private:

	/// <summary>
	/// Class of the object to save the game from the Load Screen
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;

public:

	FString GetDefaultMapName() const { return DefaultMapName; }
	FName GetDefaultPlayerStartTag() const { return DefaultPlayerStartTag; }
	FString GetDefaultMapAssetName() const { return DefaultMap.ToSoftObjectPath().GetAssetName(); }

};
