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
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// Location to set this Actor's Mesh to
	/// if it has the movement effect applied to it
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FVector CalculatedLocation;

	/// <summary>
	/// Rotation to set this Actor's Mesh to
	/// if it has the movement effect applied to it
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FRotator CalculatedRotation;

	/// <summary>
	/// Whether or not this Actor should have a rotation effect
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	bool bRotates = false;

	/// <summary>
	/// Rate of Rotation
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float RotationRate = 45.f;

	/// <summary>
	/// Function to start the rotation effect
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void StartRotation();

	/// <summary>
	/// Whether this Actor should move by following a sine wave curve
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	bool bSinusoidalMovement = false;

	/// <summary>
	/// Function to start the movement on a sine wave curve
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void StartSinusoidalMovement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float SineAmplitude = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float SinePeriodConstant = 1.f;

	/// <summary>
	/// Initial location of this Actor when spawning
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	FVector InitialLocation;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied Effects")
	float ActorLevel = 1.f;

private:

	/// <summary>
	/// Time to keep track of the sinusoidal movement
	/// </summary>
	float RunningTime = 0.f;

	/// <summary>
	/// Function to move this Actor in a sinusoidal movement
	/// </summary>
	void ItemMovement(float DeltaTime);

};
