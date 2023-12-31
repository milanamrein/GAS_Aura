// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HighlightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
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
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;

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
