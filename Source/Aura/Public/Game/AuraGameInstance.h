// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AuraGameInstance.generated.h"

/**
 * Game Instance class for Aura
 */
UCLASS()
class AURA_API UAuraGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Which PlayerStart to choose when loading up a Level
	/// </summary>
	UPROPERTY()
	FName PlayerStartTag = FName();

	/// <summary>
	/// Name of the LoadSlot to load from disk
	/// </summary>
	UPROPERTY()
	FString LoadSlotName = FString();

	/// <summary>
	/// Index of the LoadSlot to load from disk
	/// </summary>
	UPROPERTY()
	int32 LoadSlotIndex = 0;

};
