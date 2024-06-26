// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Actor/AuraProjectile.h"
#include "AuraFireBall.generated.h"

/**
 * Fire Ball Actor class for the FireBlast Ability
 */
UCLASS()
class AURA_API AAuraFireBall : public AAuraProjectile
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// BP Function to start a Timeline for the outgoing FireBalls
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void StartOutgoingTimeline();

	/// <summary>
	/// Actor to return to when this
	/// Fire Ball is finished spawning
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> ReturnToActor;

	/// <summary>
	/// Damage Effect Params for the Explosion Radial Damage.
	/// Can be set from BP.
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FDamageEffectParams ExplosionDamageParams;

protected:
	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnHit() override;

};
