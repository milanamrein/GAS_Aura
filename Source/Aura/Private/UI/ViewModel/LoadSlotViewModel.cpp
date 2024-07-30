// Copyright Milán Amrein


#include "UI/ViewModel/LoadSlotViewModel.h"

void ULoadSlotViewModel::InitializeSlot()
{
	// Broadcast Slot Status
	const int32 WidgetSwitcherIndex = SlotStatus.GetValue();
	SetWidgetSwitcherIndexDelegate.Broadcast(WidgetSwitcherIndex);
}

void ULoadSlotViewModel::SetPlayerName(FString InPlayerName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, InPlayerName);
}

void ULoadSlotViewModel::SetMapName(FString InMapName)
{
	UE_MVVM_SET_PROPERTY_VALUE(MapName, InMapName);
}
