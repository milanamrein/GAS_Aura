// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UAnimMontage;
class UNiagaraSystem;
class UDebuffNiagaraComponent;

/**
 * Base Character class for all characters
 */
UCLASS(Abstract) // can't drag an abstract class into the level
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	// Getter from IAbilitySystemInterface to implement GAS
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// Getter for the AttributeSet
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	//~ Begin Combat Interface
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;
	virtual int32 GetMinionCount_Implementation() override;
	virtual void IncrementMinionCount_Implementation(int32 Amount) override;
	virtual ECharacterClass GetCharacterClass_Implementation() override;
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() override;
	virtual FOnDeath& GetOnDeathDelegate() override;
	virtual USkeletalMeshComponent* GetWeapon_Implementation() override;
	bool IsShocked_Implementation() const override;
	void SetIsShocked_Implementation(bool bInShock) override;
	//~ End Combat Interface

	/// <summary>
	/// Delegate for when the Character's ASC has been
	/// initialized
	/// </summary>
	FOnASCRegistered OnASCRegisteredDelegate;

	/// <summary>
	/// Delegate for when the Character dies
	/// </summary>
	FOnDeath OnDeathDelegate;

	/// <summary>
	/// Multicast RPC to handle Character death
	/// on all machines
	/// </summary>
	/// <param name="DeathImpulse">Direction of the Impulse the Character receives upon death</param>
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath(const FVector& DeathImpulse);

	/// <summary>
	/// Array containing all the various Attack Montages
	/// the Character has based on its Gameplay Tags
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Combat")
	TArray<FTaggedMontage> AttackMontages;

	/// <summary>
	/// Boolean for whether or not this Character is in a Burned state
	/// </summary>
	UPROPERTY(ReplicatedUsing = OnRep_Burned, BlueprintReadOnly)
	bool bIsBurned = false;

	UFUNCTION()
	virtual void OnRep_Burned();

	/// <summary>
	/// Boolean for whether or not this Character is in a Stunned state
	/// </summary>
	UPROPERTY(ReplicatedUsing=OnRep_Stunned, BlueprintReadOnly)
	bool bIsStunned = false;

	UFUNCTION()
	virtual void OnRep_Stunned();

	/// <summary>
	/// Boolean for whether or not this Character is being Shocked
	/// </summary>
	UPROPERTY(Replicated, BlueprintReadOnly)
	bool bShocked = false;

protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// Function to initialize Ability Actor Info for GAS
	/// </summary>
	virtual void InitAbilityActorInfo();

	// new standard for member variables; has some editor features e.g. access tracking, optional lazy loading
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName LeftHandTipSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName RightHandTipSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName TailSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 600.f;

	bool bDead = false;
	
	/// <summary>
	/// Callback function to when the Stun Tag changes
	/// </summary>
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

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

	/// <summary>
	/// Niagara System for blood particles
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	UNiagaraSystem* BloodEffect;

	/// <summary>
	/// Sound made by the Character when it dies
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	USoundBase* DeathSound;

	/// <summary>
	/// Number of Minions a Character can have.
	/// Each Character can have minions (e.g. Aura can have a pet companion)
	/// </summary>
	int32 MinionCount = 0;

	/// <summary>
	/// Character Class; Warrior by default.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	/// <summary>
	/// NiagaraComponent for Burn Debuff
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDebuffNiagaraComponent> BurnDebuffComponent;

	/// <summary>
	/// NiagaraComponent for Stun Debuff
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDebuffNiagaraComponent> StunDebuffComponent;

private:

	/// <summary>
	/// Array of Character Gameplay Abilities at startup
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	/// <summary>
	/// Array of Gameplay Abilities that are passive
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
