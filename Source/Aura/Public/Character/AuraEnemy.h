// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;

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
	virtual void Die() override;
	//~ End Combat Interface

	/// <summary>
	/// Delegate to broadcast to Widgets when Enemy Health is changed
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	/// <summary>
	/// Delegate to broadcast to Widgets when Enemy Max Health is changed
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	/// <summary>
	/// Callback function to when the HitReact Tag is added/removed
	/// from the Enemy's ASC
	/// </summary>
	/// <param name="CallbackTag">The tag itself</param>
	/// <param name="NewCount">New Tag Count</param>
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	/// <summary>
	/// Boolean for whether or not the Enemy character
	/// is hit reacting
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	/// <summary>
	/// Enemy's Level. Does not replicate because checking the
	/// Enemy's level is only needed on the server.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
		int32 Level = 1;

	/// <summary>
	/// Enemy's Character Class; Warrior by default.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
		ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UWidgetComponent> HealthBar;
};
