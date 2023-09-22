// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract) // can't drag an abstract class into the level
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;

	// new standard for member variables; has some editor features e.g. access tracking, optional lazy loading
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
