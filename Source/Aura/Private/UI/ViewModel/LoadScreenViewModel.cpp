// Copyright Milán Amrein


#include "UI/ViewModel/LoadScreenViewModel.h"
#include "UI/ViewModel/LoadSlotViewModel.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Game/AuraGameInstance.h"

void ULoadScreenViewModel::InitializeLoadSlots()
{
	LoadSlot_0 = NewObject<ULoadSlotViewModel>(this, LoadSlotViewModelClass);
	LoadSlot_0->LoadSlotName = FString("LoadSlot_0");
	LoadSlot_0->SlotIndex = 0;
	LoadSlots.Add(0, LoadSlot_0);

	LoadSlot_1 = NewObject<ULoadSlotViewModel>(this, LoadSlotViewModelClass);
	LoadSlot_1->LoadSlotName = FString("LoadSlot_1");
	LoadSlot_1->SlotIndex = 1;
	LoadSlots.Add(1, LoadSlot_1);

	LoadSlot_2 = NewObject<ULoadSlotViewModel>(this, LoadSlotViewModelClass);
	LoadSlot_2->LoadSlotName = FString("LoadSlot_2");
	LoadSlot_2->SlotIndex = 2;
	LoadSlots.Add(2, LoadSlot_2);
}

ULoadSlotViewModel* ULoadScreenViewModel::GetLoadSlotViewModelByIndex(int32 Index) const
{
	return LoadSlots.FindChecked(Index);
}

void ULoadScreenViewModel::NewSlotButtonPressed(int32 Slot, const FString& EnteredName)
{
	if (AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this))) {
		// Set Saved Data
		LoadSlots[Slot]->SetMapName(AuraGameMode->GetDefaultMapName());
		LoadSlots[Slot]->SetPlayerName(EnteredName);
		LoadSlots[Slot]->SetPlayerLevel(1);
		LoadSlots[Slot]->SlotStatus = Taken;
		LoadSlots[Slot]->PlayerStartTag = AuraGameMode->GetDefaultPlayerStartTag();

		// Save Game
		AuraGameMode->SaveSlotData(LoadSlots[Slot], Slot);
		LoadSlots[Slot]->InitializeSlot();

		// Save Slot in GameInstance
		if (UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(AuraGameMode->GetGameInstance())) {
			AuraGameInstance->LoadSlotName = LoadSlots[Slot]->LoadSlotName;
			AuraGameInstance->LoadSlotIndex = LoadSlots[Slot]->SlotIndex;
			AuraGameInstance->PlayerStartTag = LoadSlots[Slot]->PlayerStartTag;
		}
	}
}

void ULoadScreenViewModel::NewGameButtonPressed(int32 Slot)
{
	// Switch to 'Enter Name' Widget
	LoadSlots[Slot]->SetWidgetSwitcherIndexDelegate.Broadcast(1);
}

void ULoadScreenViewModel::SelectSlotButtonPressed(int32 Slot)
{
	for (const TTuple<int32, ULoadSlotViewModel*> LoadSlot : LoadSlots) {
		// Disable selected Slot's button, enable rest
		if (LoadSlot.Key == Slot) {
			LoadSlot.Value->EnableSelectSlotButtonDelegate.Broadcast(false);
		}
		else {
			LoadSlot.Value->EnableSelectSlotButtonDelegate.Broadcast(true);
		}
	}
	SelectedSlot = LoadSlots[Slot];
	SlotSelectedDelegate.Broadcast();
}

void ULoadScreenViewModel::DeleteButtonPressed()
{
	// Delete Saved Game Data from Load Slot
	if (IsValid(SelectedSlot)) {
		AAuraGameModeBase::DeleteSlot(SelectedSlot->LoadSlotName, SelectedSlot->SlotIndex);
		SelectedSlot->SlotStatus = Vacant;
		SelectedSlot->InitializeSlot();
		SelectedSlot->EnableSelectSlotButtonDelegate.Broadcast(true); // reset 'Select Slot' button
	}
}

void ULoadScreenViewModel::PlayButtonPressed()
{
	if (AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this))) {
		if (UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(AuraGameMode->GetGameInstance())) {
			AuraGameInstance->PlayerStartTag = SelectedSlot->PlayerStartTag;
			AuraGameInstance->LoadSlotName = SelectedSlot->LoadSlotName;
			AuraGameInstance->LoadSlotIndex = SelectedSlot->SlotIndex;
			
			if (IsValid(SelectedSlot)) {
				AuraGameMode->TravelToMap(SelectedSlot);
			}
		}
	}
}

void ULoadScreenViewModel::LoadData()
{
	if (AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this))) {
		for (const TTuple<int32, ULoadSlotViewModel*> LoadSlot : LoadSlots) {
			ULoadScreenSaveGame* SaveObject = AuraGameMode->GetSaveSlotData(LoadSlot.Value->LoadSlotName, LoadSlot.Key);
			LoadSlot.Value->SlotStatus = SaveObject->SaveSlotStatus;
			LoadSlot.Value->SetPlayerName(SaveObject->PlayerName);
			LoadSlot.Value->SetPlayerLevel(SaveObject->PlayerLevel);
			LoadSlot.Value->SetMapName(SaveObject->MapName);
			LoadSlot.Value->PlayerStartTag = SaveObject->PlayerStartTag;
			LoadSlot.Value->InitializeSlot();
		}
	}
}
