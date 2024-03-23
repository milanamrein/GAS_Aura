// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilityInfo.generated.h"

class UGameplayAbility;

/**
* Struct for storing all information related to Gameplay Abilities
*/
USTRUCT(BlueprintType)
struct FAuraAbilityInfo {
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();

	/// <summary>
	/// What Input does this Ability has been assigned to
	/// We only enable Read in BP because this will be changed dynamically from code by the Player
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();

	/// <summary>
	/// What Status the Ability has
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag StatusTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CooldownTag = FGameplayTag();

	/// <summary>
	/// Type of the Ability: Offensive or Passive
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityType = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UTexture2D> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UMaterialInterface> BackgroundMaterial = nullptr;

	/// <summary>
	/// Level requirement for the Ability
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 LevelRequirement = 1;

	/// <summary>
	/// The Ability class itself from which the ASC
	/// can create an instance of the Ability
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> Ability;
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
