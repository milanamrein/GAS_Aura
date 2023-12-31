// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * Asset Manager Singleton
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Static Getter for getting the Asset Manager Singleton
	/// </summary>
	static UAuraAssetManager& Get();

protected:

	/// <summary>
	/// Function to start the initial loading for our assets for the game
	/// </summary>
	virtual void StartInitialLoading() override;
};
