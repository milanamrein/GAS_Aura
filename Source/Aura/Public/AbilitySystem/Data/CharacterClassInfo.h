// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;

/**
 * Enum for categorizing Character Classes
 */
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist,
	Warrior,
	Ranger
};

/**
 * Struct storing information for each Character Class
 */
USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	/// <summary>
	/// Gameplay Effect to apply Primary Attributes
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
};

/**
 * Data Asset class for storing all the data related to Character Classes
 */
UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Map storing Character Class information for each Character Class
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;

	/// <summary>
	/// Gameplay Effect to apply Secondary Attributes shared among all Classes
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	/// <summary>
	/// Gameplay Effect to apply Vital Attributes shared among all Classes
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	/// <summary>
	/// Function to return Character Class information based on Character Class
	/// </summary>
	/// <param name="CharacterClass">CharacterClass enum</param>
	/// <returns>CharacterClassDefaultInfo struct</returns>
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);

};
