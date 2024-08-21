// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HighlightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UHighlightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for highlighting various objects in the world when hovering over them
 */
class AURA_API IHighlightInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void HighlightActor();

	UFUNCTION(BlueprintNativeEvent)
	void UnHighlightActor();

	UFUNCTION(BlueprintNativeEvent)
	void SetMoveToLocation(FVector& OutDestination);

	/// <summary>
	/// Function to set the Target to rotate (MotionWarp) towards
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetTarget(AActor* InTarget);

	/// <summary>
	/// Function to get the Target Actor
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AActor* GetTarget() const;
};
