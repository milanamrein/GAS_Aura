// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Engine/TargetPoint.h"
#include "AuraEnemySpawnPoint.generated.h"

class AAuraEnemy;

/**
 * Target Point class to spawn Enemies at
 */
UCLASS()
class AURA_API AAuraEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Function to spawn an Enemy at this TargetPoint
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	/// <summary>
	/// Class to spawn an Enemy based on
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Class")
	TSubclassOf<AAuraEnemy> EnemyClass;

	/// <summary>
	/// Enemy's Level
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Class")
	int32 EnemyLevel = 1;

	/// <summary>
	/// Enemy's Class
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Class")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
};
