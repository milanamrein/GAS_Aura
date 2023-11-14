// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UAnimMontage;

/**
 * Base Character class for all characters
 */
UCLASS(Abstract) // can't drag an abstract class into the level
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	// Getter from IAbilitySystemInterface to implement GAS
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// Getter for the AttributeSet
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die() override;

	/// <summary>
	/// Multicast RPC to handle Character death
	/// on all machines
	/// </summary>
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// Function to initialize Ability Actor Info for GAS
	/// </summary>
	virtual void InitAbilityActorInfo();

	// new standard for member variables; has some editor features e.g. access tracking, optional lazy loading
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	virtual FVector GetCombatSocketLocation() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	/// <summary>
	/// Instant GameplayEffect class containing initial values
	/// for Primary Attributes of this Character
	/// </summary>
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	/// <summary>
	/// Infinite GameplayEffect class containing initial values
	/// for Secondary Attributes of this Character.
	/// Depends on Primary Attributes so whenever Primary Attributes change
	/// these Attributes adjust accordingly.
	/// </summary>
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	/// <summary>
	/// Instant GameplayEffect class containing initial values
	/// for Vital Attributes of this Character.
	/// </summary>
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	/// <summary>
	/// Function to apply a custom GameplayEffect to the Character
	/// </summary>
	/// <param name="GameplayEffectClass">GameplayEffect class to apply an instance of</param>
	/// <param name="Level">Effect level</param>
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	
	/// <summary>
	/// Function to initialize all Default Attribute values of the Character
	/// </summary>
	virtual void InitializeDefaultAttributes() const;

	/// <summary>
	/// Function to grant abilities to the Character
	/// </summary>
	void AddCharacterAbilities();

	/// <summary>
	/// Material Instance for dissolve effect when Character dies
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	/// <summary>
	/// Material Instance for the weapon's dissolve effect when Character dies
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	/// <summary>
	/// Function that creates a dynamic Material Instance to swap to
	/// the Dissolve MI so the dead Character can dissolve
	/// </summary>
	void Dissolve();

	//// <summary>
	/// BP implementable Event that starts a timeline for dissolving
	/// </summary>
	/// <param name="DynamicMaterialInstance">Dynamic dissolve MI</param>
	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	//// <summary>
	/// BP implementable Event that starts a timeline for dissolving the Weapon
	/// </summary>
	/// <param name="DynamicMaterialInstance">Dynamic dissolve MI</param>
	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

private:

	/// <summary>
	/// Array of Character Gameplay Abilities at startup
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
