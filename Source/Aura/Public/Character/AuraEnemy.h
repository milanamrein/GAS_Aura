// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "AuraEnemy.generated.h"

/**
 * Character class for the Enemy
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IHighlightInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();

	//~ Begin Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//~ End Enemy Interface

	//~ Begin Combat Interface
	virtual int32 GetCharacterLevel() override;
	//~ End Combat Interface

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	/// <summary>
	/// Enemy's Level. Does not replicate because checking the
	/// Enemy's level is only needed on the server.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
