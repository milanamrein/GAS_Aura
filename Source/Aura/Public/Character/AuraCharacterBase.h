// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * Base Character class for all characters
 */
UCLASS(Abstract) // can't drag an abstract class into the level
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	// Getter from IAbilitySystemInterface to implement GAS
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// Getter for the AttributeSet
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	// new standard for member variables; has some editor features e.g. access tracking, optional lazy loading
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
