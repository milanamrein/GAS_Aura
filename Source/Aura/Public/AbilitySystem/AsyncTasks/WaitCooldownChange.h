// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"
#include "ActiveGameplayEffectHandle.h"
#include "WaitCooldownChange.generated.h"

class UAbilitySystemComponent;
struct FGameplayEffectSpec;

// Delegate type for broadcasting Cooldown duration
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCooldownChangeSignature, float, TimeRemaining);

/**
 * Async Task to listen/wait for the Cooldown state to change (start, end)
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = "AsyncTask"))
class AURA_API UWaitCooldownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Delegate for when the Cooldown starts
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownStart;
	
	/// <summary>
	/// Delegate for when the Cooldown ends
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownEnd;

	/// <summary>
	/// Factory function to create an instance of this Async Task class
	/// </summary>
	/// <param name="AbilitySystemComponent">ASC to listen to when a Cooldown Effect has been applied</param>
	/// <param name="CooldownTag">Tag for the SpellGlobe Widget to know what specific Cooldown it is listening to</param>
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UWaitCooldownChange* WaitForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& InCooldownTag);

	/// <summary>
	/// Function to cleanup any resources when the widget is destroyed (this Task ends)
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;

	FGameplayTag CooldownTag;

	/// <summary>
	/// Callback function to when the Cooldown Tag
	/// has been changed
	/// </summary>
	void CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount);

	/// <summary>
	/// Callback function to when the Cooldown Gameplay Effect
	/// has been added
	/// </summary>
	void OnActiveEffectAdded(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveEffectHandle);
};
