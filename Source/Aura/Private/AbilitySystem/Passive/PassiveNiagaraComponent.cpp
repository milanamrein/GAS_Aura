// Copyright Milán Amrein


#include "AbilitySystem/Passive/PassiveNiagaraComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Interaction/CombatInterface.h"
#include "AuraGameplayTags.h"

UPassiveNiagaraComponent::UPassiveNiagaraComponent()
{
	bAutoActivate = false;
}

void UPassiveNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();

	// Bind callback to ActivateEffect delegate
	if (UAuraAbilitySystemComponent* AuraASC = 
		Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()))) {
		AuraASC->ActivatePassiveEffectDelegate.AddUObject(this, &UPassiveNiagaraComponent::OnPassiveActivate);
		ActivateIfMissedBroadcast(AuraASC);
	}
	else if (ICombatInterface* CombatActor = Cast<ICombatInterface>(GetOwner())) { // if ASC is not yet valid, bind through the Combat Interface
		CombatActor->GetOnASCRegisteredDelegate().AddLambda([this](UAbilitySystemComponent* ASC) {
			if (UAuraAbilitySystemComponent* AuraASC =
			Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()))) {
				AuraASC->ActivatePassiveEffectDelegate.AddUObject(this, &UPassiveNiagaraComponent::OnPassiveActivate);
				ActivateIfMissedBroadcast(AuraASC);
			}
		});
	}
}

void UPassiveNiagaraComponent::OnPassiveActivate(const FGameplayTag& AbilityTag, bool bActivate)
{
	if (!AbilityTag.MatchesTagExact(PassiveSpellTag)) return;

	if (bActivate && !IsActive()) { // only Activate when it is not Active
		Activate();
	}
	else {
		Deactivate();
	}
}

void UPassiveNiagaraComponent::ActivateIfMissedBroadcast(UAuraAbilitySystemComponent* AuraASC)
{
	// if this component missed the Delegate Broadcast, activate Passive Ability if Equipped
	if (AuraASC->bStartupAbilitiesGiven &&
		AuraASC->GetStatusFromAbilityTag(PassiveSpellTag).MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Equipped)) {
		Activate();
	}
}
