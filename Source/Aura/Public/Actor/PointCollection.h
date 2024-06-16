// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointCollection.generated.h"

/**
* Actor for handling the collection of Points in the Magic Circle
*/
UCLASS()
class AURA_API APointCollection : public AActor
{
	GENERATED_BODY()
	
public:	
	APointCollection();

	/// <summary>
	/// Function to get an array of Points
	/// </summary>
	/// <param name="GroundLocation">The center location to fetch the Points around</param>
	/// <param name="NumPoints">Number of Points to get</param>
	/// <param name="YawOverride">Rotation Yaw override</param>
	UFUNCTION(BlueprintPure)
	TArray<USceneComponent*> GetGroundPoints(const FVector& GroundLocation, int32 NumPoints, float YawOverride = 0.f);

protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// The collection of Points where an ArcandShard can be spawned at
	/// </summary>
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<USceneComponent*> Points;

	/// <summary>
	/// Maximum number of Points in the Collection
	/// </summary>
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 MaxNumOfPoints = 11;
};
