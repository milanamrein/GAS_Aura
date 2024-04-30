// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameplayTagContainer.h"
#include "DebuffNiagaraComponent.generated.h"

/**
 * Niagara Component Class for Debuffs
 */
UCLASS()
class AURA_API UDebuffNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()

public:
	
	UDebuffNiagaraComponent();

	UPROPERTY(VisibleAnywhere)
	FGameplayTag DebuffTag;
	
protected:
	
	virtual void BeginPlay() override;

	/// <summary>
	/// Callback function to when a Debuff Tag has changed; can be bound to a delegate on the ASC;
	/// Used to activate/deactivate this NiagaraComponent
	/// </summary>
	void DebuffTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	/// <summary>
	/// Callback function to when the Owner of this Component is dead
	/// </summary>
	void OnOwnerDeath(AActor* DeadOwner);
};
