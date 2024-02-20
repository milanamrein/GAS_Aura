// Copyright Milán Amrein


#include "AbilitySystem/AsyncTasks/WaitCooldownChange.h"
#include "AbilitySystemComponent.h"

UWaitCooldownChange* UWaitCooldownChange::WaitForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& InCooldownTag)
{
	UWaitCooldownChange* WaitCooldownChange = NewObject<UWaitCooldownChange>();
	WaitCooldownChange->ASC = AbilitySystemComponent;
	WaitCooldownChange->CooldownTag = InCooldownTag;
	
	if (!IsValid(AbilitySystemComponent) || !InCooldownTag.IsValid()) {
		WaitCooldownChange->EndTask();
		return nullptr;
	}

	// To know when a Cooldown Tag has been removed
	AbilitySystemComponent->RegisterGameplayTagEvent(
		InCooldownTag, 
		EGameplayTagEventType::NewOrRemoved
	)
	.AddUObject(
		WaitCooldownChange, // can't use "this" in a static function
		&UWaitCooldownChange::CooldownTagChanged
	);

	// To know when a Cooldown Gameplay Effect has been applied
	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitCooldownChange, &UWaitCooldownChange::OnActiveEffectAdded);

	return WaitCooldownChange;
}

void UWaitCooldownChange::EndTask()
{
	if (!IsValid(ASC)) return;
	// Remove CooldownTagChanged from registered ASC delegate list
	ASC->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UWaitCooldownChange::CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount)
{
	if (NewCount == 0) { // Cooldown has been removed
		CooldownEnd.Broadcast(0.f); // Cooldown has 0 sec on it, it ended
	}
}

void UWaitCooldownChange::OnActiveEffectAdded(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	// Get Asset Tags
	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);

	// Get Granted Tags
	FGameplayTagContainer GrantedTags;
	SpecApplied.GetAllGrantedTags(GrantedTags);

	// Check if any of the above contains our Cooldown Tag
	if (AssetTags.HasTagExact(CooldownTag) || GrantedTags.HasTagExact(CooldownTag)) {
		// Effect we applied is a Cooldown GE so broadcast CooldownStart delegate
		FGameplayEffectQuery GameplayEffectQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTag.GetSingleTagContainer());
		TArray<float> TimesRemaining = ASC->GetActiveEffectsTimeRemaining(GameplayEffectQuery); // Get time remaining for countdown
		if (TimesRemaining.Num() > 0) {
			// We only have one element, but GameplayEffectQuery can return with multiple Tags that can have time remainings
			// so we are getting the longest/highest time from the array			
			float TimeRemaining = TimesRemaining[0];
			for (int32 i = 0; i < TimesRemaining.Num(); i++) {
				if (TimesRemaining[i] > TimeRemaining) {
					TimeRemaining = TimesRemaining[i];
				}
			}

			// Broadcast start delegate
			CooldownStart.Broadcast(TimeRemaining);
		}
	}
}
