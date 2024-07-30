// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "LoadScreenViewModel.generated.h"

// Delegate type to broadcast when a Slot is selected
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotSelected);

class ULoadSlotViewModel;

/**
 * ViewModel class for the Loading Screen
 */
UCLASS(Blueprintable)
class AURA_API ULoadScreenViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Class to create the Load Slot Widget from
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULoadSlotViewModel> LoadSlotViewModelClass;
	
	/// <summary>
	/// Delegate to broadcast when a Slot is selected
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FSlotSelected SlotSelectedDelegate;

	/// <summary>
	/// Function to initialize all the Slots on this Load Screen
	/// </summary>
	void InitializeLoadSlots();

	/// <summary>
	/// Get a Load Slot ViewModel from the LoadSlots Map by its Index
	/// </summary>
	UFUNCTION(BlueprintPure)
	ULoadSlotViewModel* GetLoadSlotViewModelByIndex(int32 Index) const;

	/// <summary>
	/// Callback function to when the 'New Slot' button is pressed
	/// on a new Slot
	/// </summary>
	/// <param name="Slot">Slot Index</param>
	/// <param name="EnteredName">Name of the saved Slot</param>
	UFUNCTION(BlueprintCallable)
	void NewSlotButtonPressed(int32 Slot, const FString& EnteredName);

	/// <summary>
	/// Callback function to when the '+' button is pressed
	/// on a new Slot
	/// </summary>
	/// <param name="Slot">Slot Index</param>
	UFUNCTION(BlueprintCallable)
	void NewGameButtonPressed(int32 Slot);

	/// <summary>
	/// Callback function to when the 'Select Slot' button is pressed
	/// on an already saved Slot
	/// </summary>
	/// <param name="Slot">Slot Index</param>
	UFUNCTION(BlueprintCallable)
	void SelectSlotButtonPressed(int32 Slot);

	/// <summary>
	/// Callback function to when the 'Delete' button is pressed
	/// when we wish to delete saved game data from a Load Slot
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void DeleteButtonPressed();

	/// <summary>
	/// Callback function to when the 'Play' button is pressed
	/// when we wish to load the saved game from a Load Slot
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void PlayButtonPressed();

	/// <summary>
	/// Function to load Saved Game data from disk
	/// </summary>
	void LoadData();

private:

	/// <summary>
	/// Map of initialized Slots
	/// </summary>
	UPROPERTY()
	TMap<int32, ULoadSlotViewModel*> LoadSlots;

	/**
	* Load Slots
	*/

	UPROPERTY()
	TObjectPtr<ULoadSlotViewModel> LoadSlot_0;

	UPROPERTY()
	TObjectPtr<ULoadSlotViewModel> LoadSlot_1;

	UPROPERTY()
	TObjectPtr<ULoadSlotViewModel> LoadSlot_2;

	/// <summary>
	/// Pointer to the currently selected Load Slot
	/// </summary>
	UPROPERTY()
	ULoadSlotViewModel* SelectedSlot;

};
