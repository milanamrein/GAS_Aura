// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "AuraGameplayTags.h"
#include "SpellMenuWidgetController.generated.h"

// Delegate type for broadcasting the status of Spend Point & Equip Buttons
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnabled, bool, bEquipButtonEnabled, FString, DescriptionString, FString, NextLevelDescriptionString);

// Delegate type for broadcasting the selected Ability's type
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForEquipSelectionSignature, const FGameplayTag&, AbilityType);

// Delegate type for broadcasting the selected Ability to be reset
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpellGlobeReassignedSignature, const FGameplayTag&, AbilityTag);

/**
* Struct for keeping track of the currently selected Ability Spell Globe
*/
struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};

/**
 * Widget Controller class for the Spell Menu
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	/// <summary>
	/// Delegate for broadcasting when the number of Spell Points
	/// has changed for the Player
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature SpellPointsChangedDelegate;

	/// <summary>
	/// Delegate for broadcasting the status of Spend Point & Equip Buttons
	/// when an Ability Spell Globe is selected on the Spell Menu
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;

	/// <summary>
	/// Delegate for broadcasting the selected Ability's type
	/// before equipping the Ability
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature WaitForEquipDelegate;

	/// <summary>
	/// Delegate for broadcasting the selected Ability's type
	/// to cancel equipping the Ability
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature StopWaitForEquipDelegate;

	/// <summary>
	/// Delegate to broadcast the reset of the selected Spell Globe
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FSpellGlobeReassignedSignature SpellGlobeReassignedDelegate;

	/// <summary>
	/// Function to call when an Ability Spell Globe has been selected
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);

	/// <summary>
	/// Function to Deselect an already selected Globe Button
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void GlobeButtonDeselect();

	/// <summary>
	/// Function to handle the Spend Point Button being pressed
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();

	/// <summary>
	/// Function to handle the Equip Button being pressed
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void EquipButtonPressed();

	/// <summary>
	/// Function to handle when a Slot is selected on
	/// the EquippedSpellRow
	/// </summary>
	/// <param name="SlotTag">InputTag of the selected Slot</param>
	/// <param name="AbilityType">Offensive or Passive Ability Slot</param>
	UFUNCTION(BlueprintCallable)
	void SpellRowGlobePressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType);

	/// <summary>
	/// Callback function to when an Ability is equipped
	/// </summary>
	void OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot);

private:

	/// <summary>
	/// Function to Enable/Disable Spell Point & Equip Buttons
	/// based on the selected Ability's status and the number of
	/// Spell Points the Player has
	/// </summary>
	static void ToggleButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton);

	/// <summary>
	/// Member for storing data about the currently selected Ability
	/// </summary>
	FSelectedAbility SelectedAbility = { FAuraGameplayTags::Get().Abilities_None, FAuraGameplayTags::Get().Abilities_Status_Locked };

	/// <summary>
	/// Member for caching the current Spell Points the Player has
	/// </summary>
	int32 CurrentSpellPoints = 0;

	/// <summary>
	/// Boolean for whether or not this Controller is waiting for
	/// the Player to select an Ability to be Equipped
	/// </summary>
	bool bWaitingForEquipSelection = false;

	/// <summary>
	/// Gameplay Tag for storing the InputTag of
	/// the currently selected Ability if it has already
	/// been equipped before
	/// </summary>
	FGameplayTag SelectedSlot;
};
