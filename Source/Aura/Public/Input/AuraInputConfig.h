// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraInputConfig.generated.h"

/**
 * Struct mapping Input Actions with Gameplay Tags
 */
USTRUCT(BlueprintType)
struct FAuraInputAction 
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly) // const can be set in the BP of this Data Asset
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag(); // can't be const
};

/**
 * Data Asset which allows to configure Inputs with Gameplay Tags
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Function to lookup any of the Input Actions that have a specific Gameplay Tag
	/// </summary>
	/// <param name="InputTag">Gameplay Tag to associate the Input Action with</param>
	/// <param name="bLogNotFound">Whether to log the error message when the Input Action is not found</param>
	/// <returns>Generic Input Action</returns>
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	/// <summary>
	/// Array containing Input Actions mapped with Gameplay Tags
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraInputAction> AbilityInputActions;

};
