// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraAbilityTypes.h"
#include "AuraProjectile.generated.h"

class USphereComponent;
class USceneComponent;
class UNiagaraSystem;
class UProjectileMovementComponent;

/**
* Actor class for Projectiles
*/
UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraProjectile();

	/// <summary>
	/// Movement component for the Projectile
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	/// <summary>
	/// Struct associated with this Projectile responsible
	/// for Damage
	/// </summary>
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true)) // can be used while spawning Projectile from BP
	FDamageEffectParams DamageEffectParams;

	/// <summary>
	/// UProperty to store the Homing Target in. Used for
	/// garbage collection as the Projectile's HomingTargetComponent is a weak ptr.
	/// </summary>
	UPROPERTY()
	TObjectPtr<USceneComponent> HomingTargetSceneComponent;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/// <summary>
	/// Function to check whether this Projectile has a valid overlap or not
	/// </summary>
	/// <param name="OtherActor">Other Actor this Projectile is overlapping with</param>
	bool IsValidOverlap(AActor* OtherActor);

	/// <summary>
	/// Sphere for the Projectile to overlap with other Actors
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Sphere;

	/// <summary>
	/// Function to when the Projectile hits a Target
	/// </summary>
	UFUNCTION(BlueprintCallable)
	virtual void OnHit();

	/// <summary>
	/// Sound component for storing the spawned LoopingSound
	/// </summary>
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;

	/// <summary>
	/// Boolean to check whether Destroy() is called before OnSphereOverlap() on clients
	/// </summary>
	bool bHit = false;

private:

	/// <summary>
	/// How long does this Projectile live if it hits nothing
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;

	/// <summary>
	/// NiagaraSystem Effect for Projectile Impact
	/// </summary>
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	/// <summary>
	/// Sound Effect for Projectile Impact
	/// </summary>
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	/// <summary>
	/// Sound Effect to spawn while Projectile is flying
	/// </summary>
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;

};
