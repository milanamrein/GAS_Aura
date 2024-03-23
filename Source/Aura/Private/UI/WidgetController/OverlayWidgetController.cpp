// Copyright Milán Amrein


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "AuraGameplayTags.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	// Initialize Attribute values - this function should be called after AttributeSet is initialized
	OnHealthChanged.Broadcast(GetAuraAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetAuraAS()->GetMaxHealth());
	OnManaChanged.Broadcast(GetAuraAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetAuraAS()->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	// Bind callbacks to delegates related to Player State change
	// Bind callbacks to XP and Level changes
	GetAuraPS()->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	GetAuraPS()->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel) {
			OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
		}
	);

	// Bind lambda callbacks to delegates related to Attributes change
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetHealthAttribute())
		.AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxHealthAttribute())
		.AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetManaAttribute())
		.AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnManaChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxManaAttribute())
		.AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
		);

	if (GetAuraASC()) {
		// Bind to when an Ability is equipped
		GetAuraASC()->AbilityEquippedDelegate.AddUObject(this, &UOverlayWidgetController::OnAbilityEquipped);

		if (GetAuraASC()->bStartupAbilitiesGiven) {
			// We don't care about binding when the Abilities are already initialized, just call the function
			BroadcastAbilityInfo();
		}
		else {
			// Bind startup function to when the Abilities have not yet been given/initialized/broadcasted
			GetAuraASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
		}

		// Bind an anonymous function (lambda) to the delegate
		GetAuraASC()->EffectAssetTagsDelegate.AddLambda([this] // capture UOverlayWidgetController
			(const FGameplayTagContainer& AssetTags) {
				for (const FGameplayTag& Tag : AssetTags) {
					// We only want "Message" Tags to be broadcasted here
					if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message")))) {
						// Broadcast DataTable Data to UI Widgets
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
		});
	}
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	const ULevelUpInfo* LevelUpInfo = GetAuraPS()->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("Unable to find LevelUpInfo. Please fill out AuraPlayerState Blueprint."));

	// Find new Level
	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num(); // Maximum number of Levels

	// Calculate XP percentage and broadcast it to Widgets
	if (Level <= MaxLevel && Level > 0) { // check if Level range is correct
		// Get requirements of current and previous Levels
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;

		// Get delta to divide the current XP by it
		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);
		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}

void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot) const
{
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
}
