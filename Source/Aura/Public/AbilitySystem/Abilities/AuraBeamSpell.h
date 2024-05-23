// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraBeamSpell.generated.h"

/**
 * Gameplay Ability class for Beams
 */
UCLASS()
class AURA_API UAuraBeamSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Function that sets the properties of this Beam Spell by taking the HitResult as input
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void StoreMouseDataInfo(const FHitResult& HitResult);

	/// <summary>
	/// Function to set the Owner Character and its PlayerController of this Beam
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void StoreOwner();

	/// <summary>
	/// Function to trace the first blocking Target of
	/// this Beam's traceline (between Aura's staff and the Mouse Cursor)
	/// </summary>
	/// <param name="BeamTargetLocation">The location of the original Target (Mouse Click)</param>
	/// <param name="BeamStartSocket">The start location of this Beam; a Weapon Socket</param>
	UFUNCTION(BlueprintCallable)
	void TraceFirstTarget(const FVector& BeamTargetLocation, const FName& BeamStartSocket);

	/// <summary>
	/// Function to handle the search for a certain amount of additional Targets in a certain proximity
	/// of the Target (Mouse Hit Target or First Target)
	/// </summary>
	/// <param name="OutAdditionalTargets">Output array of additional Targets</param>
	UFUNCTION(BlueprintCallable)
	void StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets);

	/// <summary>
	/// Callback function to the OnDeath delegate for the
	/// Primary (Mouse Hit or First) Target
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void PrimaryTargetDied(AActor* DeadActor);

	/// <summary>
	/// Callback function to the OnDeath delegate for a single
	/// Additional Target
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void AdditionalTargetDied(AActor* DeadActor);

protected:

	/// <summary>
	/// Location where the Player clicks with the mouse
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	FVector MouseHitLocation;

	/// <summary>
	/// Actor that is clicked by the Player
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<AActor> MouseHitActor;

	/// <summary>
	/// Ability's Owner PlayerController
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<APlayerController> OwnerPlayerController;

	/// <summary>
	/// Ability's Owner Character
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<ACharacter> OwnerCharacter;

	/// <summary>
	/// The radius at which this Beam should check for additional Targets
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	FScalableFloat BeamRadius;

	/// <summary>
	/// Maximum number of Shock Targets at once
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	int32 MaxTargets = 5;
};
