// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class ULevelUpInfo;

// Delegate signature for broadcasting Player Stats (XP, Level etc.)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/);

/**
 * PlayerState class for Aura
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// Getter from IAbilitySystemInterface to implement GAS
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// Getter for the AttributeSet
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	/// <summary>
	/// Pointer holding the information of the Player's
	/// current Level
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;

	// Getters
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetXP() const { return XP; }
	
	// Setters
	void SetXP(int32 InXP);
	void SetLevel(int32 InLevel);
	
	// Add
	void AddToXP(int32 InXP);
	void AddToLevel(int32 InLevel);

	/// <summary>
	/// Delegate for broadcasting when the XP has changed/set
	/// </summary>
	FOnPlayerStatChanged OnXPChangedDelegate;

	/// <summary>
	/// Delegate for broadcasting when the Level has changed/set
	/// </summary>
	FOnPlayerStatChanged OnLevelChangedDelegate;

protected:

	// For the Player Character we handle these in PlayerState
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	/// <summary>
	/// Variable for the Player's Level
	/// </summary>
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;

	/// <summary>
	/// Variable for the Player's XP
	/// </summary>
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP)
	int32 XP = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);
};
