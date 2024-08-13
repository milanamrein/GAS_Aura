// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USaveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for saving Game Data
 */
class AURA_API ISaveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/// <summary>
	/// Function to check whether the Actor's Transform
	/// should be updated or not
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsMoveable();

	/// <summary>
	/// Function to load the saved Actor
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LoadActor();
};
