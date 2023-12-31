// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

// Delegate type for TargetData under cursor
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);

/**
 * Ability Task class to get Target Data under mouse cursor
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Factory function to create an instance of class UTargetDataUnderMouse
	/// </summary>
	/// <param name="OwningAbility">Gameplay Ability that owns this Task. Default is Self(this) in BP.</param>
	/// <returns>UTargetDataUnderMouse instance.</returns>
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TargetDataUnderMouse", HidePin = "OwningAbility",
		DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	/// <summary>
	/// Delegate for broadcasting TargetData Handle under mouse cursor
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

private:

	virtual void Activate() override;

	/// <summary>
	/// Function to send Target Data to the server from
	/// the locally controlled machine
	/// </summary>
	void SendMouseCursorData();

	/// <summary>
	/// Callback function to when the Target Data is set on the server
	/// </summary>
	/// <param name="DataHandle">Data Handle containing Target Data</param>
	/// <param name="ActivationTag">Activation Tag</param>
	void OnTargetReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
};
