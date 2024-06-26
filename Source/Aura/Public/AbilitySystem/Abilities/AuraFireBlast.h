// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraFireBlast.generated.h"

class AAuraFireBall;

/**
 * Ability class for Fire Blast Ability
 */
UCLASS()
class AURA_API UAuraFireBlast : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
	
public:

	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 NextLevel) override;
	
	/// <summary>
	/// Function to spawn Fire Balls
	/// </summary>
	/// <returns>Fire Balls spawned</returns>
	UFUNCTION(BlueprintCallable)
	TArray<AAuraFireBall*> SpawnFireBalls();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Fire Blast")
	int32 NumFireBalls = 12;

private:

	/// <summary>
	/// Class to spawn Fire Balls from
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAuraFireBall> FireBallClass;
};
