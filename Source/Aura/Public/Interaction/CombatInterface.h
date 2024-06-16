// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "CombatInterface.generated.h"

class UAnimMontage;
class UNiagaraSystem;
class UAbilitySystemComponent;

// Delegate type for when the Combat Actor's ASC has been initialized
DECLARE_MULTICAST_DELEGATE_OneParam(FOnASCRegistered, UAbilitySystemComponent*);

// Delegate type for when the Combat Actor dies
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AActor*, DeadActor);

// Delegate type for broadcasting Damage
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamageSignature, float /*DamageAmount*/);

/**
 * Struct linking Gameplay Tags together with Animation Montages and Impact Sounds
 */
USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	/// <summary>
	/// Animation Montage
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;

	/// <summary>
	/// Tag that identifies the Animation Montage
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;

	/// <summary>
	/// Tag to identify the Combat Socket
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SocketTag;

	/// <summary>
	/// Sound to play on impact
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* ImpactSound = nullptr;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

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
	UFUNCTION(BlueprintNativeEvent)
	int32 GetPlayerLevel();

	/// <summary>
	/// Function to return a Combat Socket location
	/// </summary>
	/// <param name="MontageTag">Gameplay Tag set in AnimMontage associated with the Socket</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);
	
	/// <summary>
	/// Function to get the Combat Actor's Weapon
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	USkeletalMeshComponent* GetWeapon();

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
	/// <param name="DeathImpulse">Direction of the Impulse the Actor receives upon death</param>
	virtual void Die(const FVector& DeathImpulse) = 0;

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

	/// <summary>
	/// Function to get the blood effect
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UNiagaraSystem* GetBloodEffect();

	/// <summary>
	/// Function that returns an FTaggedMontage based on a FGameplayTag
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTaggedMontage GetTaggedMontageByTag(const FGameplayTag& MontageTag);

	/// <summary>
	/// Function that returns the number of Minions a Character is currently having
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetMinionCount();

	/// <summary>
	/// Function to increment the number of Minions a Character currently has
	/// when summoning a Minion
	/// </summary>
	/// <param name="Amount">Amount to increment by</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IncrementMinionCount(int32 Amount);

	/// <summary>
	/// Function to get the Class of the Character
	/// that implements this Interface
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ECharacterClass GetCharacterClass();

	/// <summary>
	/// Function to return the delegate of when the Actor's
	/// ASC has been initialized
	/// </summary>
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() = 0;

	/// <summary>
	/// Function to return the delegate of when the Actor dies
	/// </summary>
	virtual FOnDeath& GetOnDeathDelegate() = 0;

	/// <summary>
	/// Function to return the delegate of when the Actor receives Damage
	/// </summary>
	virtual FOnDamageSignature& GetOnDamageDelegate() = 0;

	/// <summary>
	/// BP function to set whether or not the Combat Actor is
	/// using their Shock Ability
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetInShockLoop(bool InLoop);

	/// <summary>
	/// Function to get whether the Combat Actor is in a Shock Loop
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsShocked() const;

	/// <summary>
	/// Function to set whether the Combat Actor is in a Shock Loop
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetIsShocked(bool bInShock);
};
