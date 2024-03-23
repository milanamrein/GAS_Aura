// Copyright Milán Amrein


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AbilitySystem/AuraAttributeSet.h"

FString UAuraGameplayAbility::GetDescription(int32 Level)
{
    return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"), L"Default Ability Name - LoremIpsum LoremIpsum LoremIpsum", Level);
}

FString UAuraGameplayAbility::GetNextLevelDescription(int32 NextLevel)
{
    return FString::Printf(TEXT("<Default>Next Level </><Level>%d</> \n <Default>Causes much more damage</>"), NextLevel);
}

FString UAuraGameplayAbility::GetLockedDescription(int32 Level)
{
    return FString::Printf(TEXT("<Default>Spell Locked Until Level: %d</>"), Level);
}

float UAuraGameplayAbility::GetManaCost(float InLevel) const
{
    float ManaCost = 0.f;
    if (const UGameplayEffect* CostEffect = GetCostGameplayEffect()) {
        for (FGameplayModifierInfo Modifier : CostEffect->Modifiers) { // should have 1 Modifier for Cost
            if (Modifier.Attribute == UAuraAttributeSet::GetManaAttribute()) { // if it is a Mana Cost Modifier
                Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost); // try to get magnitude's float value
                break; // end loop if cost is found
            }
        }
    }

    return ManaCost;
}

float UAuraGameplayAbility::GetCooldown(float InLevel) const
{
    float Cooldown = 0.f;
    if (const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect()) {
        // Cooldown is an Effect without any Modifiers, it is a duration based Effect
        CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, Cooldown);
    }

    return Cooldown;
}
