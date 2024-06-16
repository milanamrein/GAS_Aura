// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraBeamSpell.h"
#include "Electrocute.generated.h"

/**
 * Beam Spell Class for Electrocute
 */
UCLASS()
class AURA_API UElectrocute : public UAuraBeamSpell
{
	GENERATED_BODY()

public:

	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 NextLevel) override;
	
};
