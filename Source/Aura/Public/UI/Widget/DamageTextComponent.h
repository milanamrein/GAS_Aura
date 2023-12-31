// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

/**
 * Widget Component class for showing Damage Text
 */
UCLASS()
class AURA_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// BP implementable Event that is called from C++ to set
	/// the Damage Text
	/// </summary>
	/// <param name="Damage">Damage as float</param>
	/// <param name="bBlockedHit">Whether or not we had a Blocked Hit</param>
	/// <param name="bCriticalHit">Whether or not we had a Critical Hit</param>
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage, bool bBlockedHit, bool bCriticalHit);
};
