// Copyright Milán Amrein


#include "UI/WidgetController/SpellMenuWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	
	// Broadcast Spell Points
	SpellPointsChangedDelegate.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	// Bind to Ability Status Changed delegate
	GetAuraASC()->AbilityStatusChangedDelegate.AddLambda(
		[this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 NewLevel) {
			// Check if the Ability is the currently selected one
			if (SelectedAbility.Ability.MatchesTagExact(AbilityTag)) {
				// Set status to new and update Buttons
				SelectedAbility.Status = StatusTag;

				bool bEnableSpendPoints = false;
				bool bEnableEquip = false;
				ToggleButtons(StatusTag, CurrentSpellPoints, bEnableSpendPoints, bEnableEquip);

				FString Description;
				FString NextLevelDescription;
				GetAuraASC()->GetDescriptionsByAbilityTag(AbilityTag, Description, NextLevelDescription);

				SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip, Description, NextLevelDescription);
			}

			if (AbilityInfo) {
				FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
				Info.StatusTag = StatusTag;
				AbilityInfoDelegate.Broadcast(Info);
			}
		}
	);

	// Bind to Ability Equipped delegate
	GetAuraASC()->AbilityEquippedDelegate.AddUObject(this, &USpellMenuWidgetController::OnAbilityEquipped);

	// Bind to Spell Point Changed delegate
	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 SpellPoints) {
			SpellPointsChangedDelegate.Broadcast(SpellPoints);
			
			// Update current Spell Points and Buttons
			CurrentSpellPoints = SpellPoints;

			bool bEnableSpendPoints = false;
			bool bEnableEquip = false;
			ToggleButtons(SelectedAbility.Status, CurrentSpellPoints, bEnableSpendPoints, bEnableEquip);

			FString Description;
			FString NextLevelDescription;
			GetAuraASC()->GetDescriptionsByAbilityTag(SelectedAbility.Ability, Description, NextLevelDescription);

			SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip, Description, NextLevelDescription);
		}
	);
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	if (bWaitingForEquipSelection) {
		// Stop Equip waiting
		FGameplayTag SelectedAbilityType = AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityType;
		StopWaitForEquipDelegate.Broadcast(SelectedAbilityType);
		bWaitingForEquipSelection = false;
	}

	// Get Spell Points & Ability Status
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	const int32 SpellPoints = GetAuraPS()->GetSpellPoints();
	FGameplayTag AbilityStatus;

	const bool bTagValid = AbilityTag.IsValid();
	const bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	const FGameplayAbilitySpec* AbilitySpec = GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);
	const bool bSpecValid = AbilitySpec != nullptr;
	if (!bTagValid || bTagNone || !bSpecValid) {
		// Ability we don't have yet (Locked) or Ability doesn't exist (Ability.None)
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else {
		AbilityStatus = GetAuraASC()->GetStatusFromSpec(*AbilitySpec);
	}

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatus;

	// Set Button booleans
	bool bEnableSpendPoints = false;
	bool bEnableEquip = false;
	ToggleButtons(AbilityStatus, SpellPoints, bEnableSpendPoints, bEnableEquip);

	FString Description;
	FString NextLevelDescription;
	GetAuraASC()->GetDescriptionsByAbilityTag(SelectedAbility.Ability, Description, NextLevelDescription);

	SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip, Description, NextLevelDescription);
}

void USpellMenuWidgetController::GlobeButtonDeselect()
{
	if (bWaitingForEquipSelection) {
		// Stop Equip waiting
		FGameplayTag SelectedAbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
		StopWaitForEquipDelegate.Broadcast(SelectedAbilityType);
		bWaitingForEquipSelection = false;
	}

	SelectedAbility.Ability = FAuraGameplayTags::Get().Abilities_None;
	SelectedAbility.Status = FAuraGameplayTags::Get().Abilities_Status_Locked;

	SpellGlobeSelectedDelegate.Broadcast(false, false, FString(), FString());
}

void USpellMenuWidgetController::SpendPointButtonPressed()
{
	// Update ASC on the Server about the currently selected Ability
	if (GetAuraASC()) {
		GetAuraASC()->ServerSpendSpellPoint(SelectedAbility.Ability);
	}
}

void USpellMenuWidgetController::EquipButtonPressed()
{
	// Wait for the Player's selection
	const FGameplayTag AbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
	WaitForEquipDelegate.Broadcast(AbilityType);
	bWaitingForEquipSelection = true;

	// Save slot of currently equipped Ability
	const FGameplayTag SelectedStatus = GetAuraASC()->GetStatusFromAbilityTag(SelectedAbility.Ability);
	if (SelectedStatus.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Equipped)) {
		SelectedSlot = GetAuraASC()->GetInputTagFromAbilityTag(SelectedAbility.Ability);
	}
}

void USpellMenuWidgetController::SpellRowGlobePressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType)
{
	if (!bWaitingForEquipSelection) return; // if we are not waiting for a selection, just return
	
	// Check selected Ability against the Slot's type
	// Cannot equip an Offensive Ability to a Passive Slot and vica versa
	const FGameplayTag& SelectedAbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
	if (!SelectedAbilityType.MatchesTagExact(AbilityType)) return;

	// Equip Ability
	GetAuraASC()->ServerEquipAbility(SelectedAbility.Ability, SlotTag);
}

void USpellMenuWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot)
{
	bWaitingForEquipSelection = false;
	FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	// Broadcast empty Info if the previous Slot is valid - equipping an already equipped Ability
	FAuraAbilityInfo LastSlotInfo;
	LastSlotInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PreviousSlot;
	LastSlotInfo.AbilityTag = GameplayTags.Abilities_None;

	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	// Broadcast current/new Slot
	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = Slot;

	AbilityInfoDelegate.Broadcast(Info);

	// Stop waiting for equipping
	StopWaitForEquipDelegate.Broadcast(AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityType);

	// Reset Spell Globe
	SpellGlobeReassignedDelegate.Broadcast(AbilityTag);
	GlobeButtonDeselect();
}

void USpellMenuWidgetController::ToggleButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	// When the Status is Unlocked or Equipped, both Buttons can be enabled if Player has SpellPoints
	// Eligible cannot be Equipped unless it becomes Unlocked
	// When Status is Locked, both Buttons must be disabled
	bShouldEnableEquipButton = AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped) || 
		AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked);
	bShouldEnableSpellPointsButton = SpellPoints > 0 && !AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Locked);
}
