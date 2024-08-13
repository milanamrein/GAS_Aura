// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "Interaction/SaveInterface.h"
#include "AuraCheckpoint.generated.h"

class USphereComponent;

/**
 * Class for Checkpoints in the game
 */
UCLASS()
class AURA_API AAuraCheckpoint : public APlayerStart, public ISaveInterface
{
	GENERATED_BODY()

public:

	AAuraCheckpoint(const FObjectInitializer& ObjectInitializer);

	virtual bool IsMoveable_Implementation() override { return false; };
	virtual void LoadActor_Implementation() override;

	/// <summary>
	/// Boolean for whether or not this Checkpoint has been
	/// reached
	/// </summary>
	UPROPERTY(SaveGame)
	bool bReached = false;

protected:

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

	/// <summary>
	/// BP Event to when we reach a checkpoint
	/// </summary>
	/// <param name="DynamicMaterialInstance">Material Instance to create in order to indicate that we reached the checkpoint</param>
	UFUNCTION(BlueprintImplementableEvent)
	void CheckpointReached(UMaterialInstanceDynamic* DynamicMaterialInstance);

	/// <summary>
	/// Function to create glowing effects on the Checkpoint Material in order to
	/// indicate that the Player has reached the Checkpoint
	/// </summary>
	void HandleGlowEffects();

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> CheckpointMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
};
