// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

class UMaterialInterface;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface specifically for Player Interactions
 * Helps to decouple PlayerState from PlayerCharacter
 */
class AURA_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/// <summary>
	/// Function to find a Level for a certain
	/// amount of XP
	/// </summary>
	UFUNCTION(BlueprintNativeEvent)
	int32 FindLevelForXP(int32 InXP) const;

	/// <summary>
	/// Function to get the Player's current XP
	/// </summary>
	UFUNCTION(BlueprintNativeEvent)
	int32 GetXP() const;

	/// <summary>
	/// Getter function to get the amount of Attribute Points
	/// the Player currently has
	/// </summary>
	UFUNCTION(BlueprintNativeEvent)
	int32 GetAttributePoints() const;

	/// <summary>
	/// Getter function to get the amount of Spell Points
	/// the Player currently has
	/// </summary>
	UFUNCTION(BlueprintNativeEvent)
	int32 GetSpellPoints() const;

	/// <summary>
	/// Function to get the Reward for
	/// Attribute Points based on the Level
	/// </summary>
	UFUNCTION(BlueprintNativeEvent)
	int32 GetAttributePointsReward(int32 Level) const;

	/// <summary>
	/// Function to get the Reward for
	/// Spell Points based on the Level
	/// </summary>
	UFUNCTION(BlueprintNativeEvent)
	int32 GetSpellPointsReward(int32 Level) const;

	/// <summary>
	/// Function to handle levelling up
	/// </summary>
	UFUNCTION(BlueprintNativeEvent)
	void LevelUp();

	/// <summary>
	/// Function to add to the Player's current XP
	/// </summary>
	/// <param name="InXP">Amount of XP to add</param>
	UFUNCTION(BlueprintNativeEvent)
	void AddToXP(int32 InXP);

	/// <summary>
	/// Function to add to the Player's current Level
	/// </summary>
	/// <param name="InLevel">Amount of Level to add</param>
	UFUNCTION(BlueprintNativeEvent)
	void AddToPlayerLevel(int32 InLevel);

	/// <summary>
	/// Function to add to the Player's current AttributePoints
	/// </summary>
	/// <param name="InAttributePoints">Amount of AttributePoints to add</param>
	UFUNCTION(BlueprintNativeEvent)
	void AddToAttributePoints(int32 InAttributePoints);

	/// <summary>
	/// Function to add to the Player's current SpellPoints
	/// </summary>
	/// <param name="InSpellPoints">Amount of SpellPoints to add</param>
	UFUNCTION(BlueprintNativeEvent)
	void AddToSpellPoints(int32 InSpellPoints);

	/// <summary>
	/// Function to spawn the Magic Circle
	/// </summary>
	/// <param name="DecalMaterial">What Material should be spawned by the Decal</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowMagicCircle(UMaterialInterface* DecalMaterial = nullptr);

	/// <summary>
	/// Function to destroy the Magic Circle
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideMagicCircle();
};
