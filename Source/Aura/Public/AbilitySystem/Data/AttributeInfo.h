// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

/**
* Struct for storing all the information related to an Attribute
*/
USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	// We do not expose this to BP edit because we will want the current value every time we want to access this struct
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/**
 * DataAsset class containing Attribute information
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Function to find an Attribute's information based on its Tag
	/// </summary>
	/// <param name="AttributeTag">Tag to search</param>
	/// <param name="bLogNotFound">Whether or not to log the error when the information is not found</param>
	/// <returns>Attribute Info struct</returns>
	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

	/// <summary>
	/// Array containing all the Attribute information for this DataSet
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
};
