// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameplayTagContainer.h"
#include "PassiveNiagaraComponent.generated.h"

class UAuraAbilitySystemComponent;

/**
 * NiagaraComponent class for Passive Spells
 */
UCLASS()
class AURA_API UPassiveNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()
	
public:

	UPassiveNiagaraComponent();

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag PassiveSpellTag;

protected:

	virtual void BeginPlay() override;

	/// <summary>
	/// Callback function to when this NiagaraComponent is activated/deactivated
	/// </summary>
	/// <param name="AbilityTag">The Ability associated with this Component</param>
	/// <param name="bActivate">Whether to activate or deactivate this Component</param>
	void OnPassiveActivate(const FGameplayTag& AbilityTag, bool bActivate);

	/// <summary>
	/// Function to Activate this Component if it misses the Delegate
	/// Broadcast upon initialization
	/// </summary>
	/// <param name="AuraASC">Ability System Component to check for activated Abilities</param>
	void ActivateIfMissedBroadcast(UAuraAbilitySystemComponent* AuraASC);
};
