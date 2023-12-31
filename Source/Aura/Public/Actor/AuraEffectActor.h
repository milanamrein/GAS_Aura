// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

/// <summary>
/// Enum on how we are going to apply the GameplayEffect
/// </summary>
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

/// <summary>
/// Enum on how we are going to remove an Infinite GameplayEffect
/// </summary>
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

/**
* Base Actor class for Gameplay Effects
*/
UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// Function to apply GameplayEffect on Target who interacts
	/// with this Actor
	/// </summary>
	/// <param name="Target">Target Actor</param>
	/// <param name="GameplayEffectClass">Class of GameplayEffect to be applied</param>
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	/// <summary>
	/// Callback function to when another Actor overlaps with this Actor
	/// </summary>
	/// <param name="TargetActor">Other Actor who is overlapping</param>
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	/// <summary>
	/// Callback function to when another Actor finishes overlapping with this Actor
	/// </summary>
	/// <param name="TargetActor">Other Actor who overlapped</param>
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	/// <summary>
	/// Boolean for whether or not to destroy this Actor on effect removal
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyOnEffectApplication = false;

	/// <summary>
	/// Boolean for whether or not to apply effects to Enemies
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bApplyEffectsToEnemies = false;

	/// <summary>
	/// Class of an Instant GameplayEffect that we want to apply
	/// to another Actor interacting with this Actor
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	/// <summary>
	/// Application Policy for Instant GameplayEffect type
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	/// <summary>
	/// Class of a Duration type GameplayEffect that we want to apply
	/// to another Actor interacting with this Actor
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	/// <summary>
	/// Application Policy for Duration GameplayEffect type
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	/// <summary>
	/// Class of a infinite type GameplayEffect that we want to apply
	/// to another Actor interacting with this Actor
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	/// <summary>
	/// Application Policy for Infinite GameplayEffect type
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	/// <summary>
	/// Removal Policy for Infinite GameplayEffect type
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	/// <summary>
	/// Map for mapping ActiveGameplayEffectHandles to AbilitySystemComponent pointers
	/// </summary>
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	/// <summary>
	/// Actor's Level
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	float ActorLevel = 1.f;
};
