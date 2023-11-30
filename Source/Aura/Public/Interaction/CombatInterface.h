// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "CombatInterface.generated.h"

/**
 * Struct linking Gameplay Tags together with Animation Montages
 */
USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class UAnimMontage;

/**
 * Interface for Combat interaction
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Function to return a Character's Level
	/// </summary>
	/// <returns>Level</returns>
	virtual int32 GetCharacterLevel();

	/// <summary>
	/// Function to return a Combat Socket location
	/// </summary>
	/// <param name="MontageTag">Gameplay Tag set in AnimMontage associated with the Socket</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);
	
	/// <summary>
	/// Function to update the Facing Target during Motion Warping
	/// </summary>
	/// <param name="Target">Target to rotate towards</param>
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent) // BlueprintImplementableEvent cannot be virtual
	void UpdateFacingTarget(const FVector& Target);

	/// <summary>
	/// Function to get the Montage when the
	/// Combat Actor is being hit
	/// </summary>
	/// <returns>HitReact Animation Montage</returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) // don't need to be virtual to be overridden in C++ and be callable in BP
	UAnimMontage* GetHitReactMontage();

	/// <summary>
	/// Function to when a Combat Actor dies
	/// </summary>
	virtual void Die() = 0;

	/// <summary>
	/// Function for whether or not the Player has died
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;

	/// <summary>
	/// Function to get the Avatar Actor
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();

	/// <summary>
	/// Function to get all the Attack Montages of the
	/// Combat Actor
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<FTaggedMontage> GetAttackMontages();
};
