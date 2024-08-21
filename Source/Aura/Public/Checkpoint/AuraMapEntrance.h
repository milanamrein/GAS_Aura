// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint/AuraCheckpoint.h"
#include "AuraMapEntrance.generated.h"

/**
 * Class for Map Entrances to transition to other Levels
 */
UCLASS()
class AURA_API AAuraMapEntrance : public AAuraCheckpoint
{
	GENERATED_BODY()
	
public:

	AAuraMapEntrance(const FObjectInitializer& ObjectInitializer);

	virtual void LoadActor_Implementation() override;

protected:

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	/// <summary>
	/// Pointer to the destination Map/Level to travel to
	/// </summary>
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> DestinationMap;

	/// <summary>
	/// Tag of the Player Start to spawn at
	/// </summary>
	UPROPERTY(EditAnywhere)
	FName DestinationPlayerStartTag;
};
