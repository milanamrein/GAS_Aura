// Copyright Milán Amrein


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	// As soon as the Ability is activated, we broadcast the location of the mouse cursor
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled()) {
		SendMouseCursorData();
	}
	else {
		// Listen for Target Data on Server
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey())
			.AddUObject(this, &UTargetDataUnderMouse::OnTargetReplicatedCallback);
		// Check whether the Target Data has already been sent and the Data has already been broadcasted and call the callback regardless
		if (!AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(), GetActivationPredictionKey())) {
			// Wait for player data to come through
			SetWaitingOnRemotePlayerData();
		}

	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	// Create Scoped Prediction Window so everything we are doing in this scope should be predicted
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	// Get Mouse Cursor Hit
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	// Create Target Data & Handle
	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);

	// Send Target Data to Server
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(), 
		GetActivationPredictionKey(), 
		DataHandle, 
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey // current Prediction Key
	);

	// Check whether we should broadcast our Ability Task delegate or not
	if (ShouldBroadcastAbilityTaskDelegates()) {
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	// Target Data has been received, don't keep it cached
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates()) {
		ValidData.Broadcast(DataHandle);
	}
}
