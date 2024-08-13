// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "LoadSlotViewModel.generated.h"

// Delegate type to broadcast the index of the Switcher to switch to
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, WidgetSwitcherIndex);

// Delegate type to broadcast the status of the 'Select' Button of this Slot
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnableSelectSlotButton, bool, bEnable);

/**
 * ViewModel class for the Load Slot
 */
UCLASS(Blueprintable)
class AURA_API ULoadSlotViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Delegate to broadcast the index of the Widget Switcher
	/// that this Slot has to switch to
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwitcherIndex SetWidgetSwitcherIndexDelegate;

	/// <summary>
	/// Delegate to broadcast whether the Select Button of this Slot
	/// is enabled or not
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FEnableSelectSlotButton EnableSelectSlotButtonDelegate;

	/// <summary>
	/// Function to initialize this Load Slot
	/// </summary>
	void InitializeSlot();
	
	/// <summary>
	/// Saved Slot's Name provided in the input
	/// which uniquely identifies the Slot
	/// </summary>
	UPROPERTY()
	FString LoadSlotName;

	/// <summary>
	/// Slot's Index in the Switcher
	/// </summary>
	UPROPERTY()
	int32 SlotIndex;

	/// <summary>
	/// Status of this Slot
	/// </summary>
	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SlotStatus;

	/// <summary>
	/// Tag of the PlayerStart the Player should start at
	/// </summary>
	UPROPERTY()
	FName PlayerStartTag;

	/**
	* Field Notifies
	*/

	void SetPlayerName(FString InPlayerName);
	void SetMapName(FString InMapName);
	void SetPlayerLevel(int32 InPlayerLevel);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	FString MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
	int32 PlayerLevel;

public:

	FString GetPlayerName() const { return PlayerName; }
	FString GetMapName() const { return MapName; }
	int32 GetPlayerLevel() const { return PlayerLevel; }

};
