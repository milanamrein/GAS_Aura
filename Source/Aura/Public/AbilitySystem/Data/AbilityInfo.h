// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilityInfo.generated.h"

/**
* Struct for storing all information related to Gameplay Abilities
*/
USTRUCT(BlueprintType)
struct FAuraAbilityInfo {
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();

	// We only enable Read in BP because this will be changed dynamically from code by the Player
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UTexture2D> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UMaterialInterface> BackgroundMaterial = nullptr;
};

/**
 * Data Asset class for storing Gameplay Abilities which are going to be
 * used during Gameplay through Inputs that are shown on the UI
 */
UCLASS()
class AURA_API UAbilityInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Array of Gameplay Abilities that can be used during Gameplay
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Information")
	TArray<FAuraAbilityInfo> AbilityInformation;

	/// <summary>
	/// Function to retrieve the Ability Information based on the AbilityTag
	/// </summary>
	/// <param name="AbilityTag">Gameplay Tag to find the Information for</param>
	/// <param name="bLogNotFound">Whether to log the error when it is not found</param>
	FAuraAbilityInfo FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound = false) const;
};
