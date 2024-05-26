// Copyright Milán Amrein


#include "AbilitySystem/Passive/PassiveNiagaraComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Interaction/CombatInterface.h"

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
	}
	else if (ICombatInterface* CombatActor = Cast<ICombatInterface>(GetOwner())) { // if ASC is not yet valid, bind through the Combat Interface
		CombatActor->GetOnASCRegisteredDelegate().AddLambda([this](UAbilitySystemComponent* ASC) {
			if (UAuraAbilitySystemComponent* AuraASC =
			Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()))) {
				AuraASC->ActivatePassiveEffectDelegate.AddUObject(this, &UPassiveNiagaraComponent::OnPassiveActivate);
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
