// Copyright Milán Amrein


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes) {
		BroadcastAttributeInfo(Pair.Key, Pair.Value()); // Value stores the address of a function so we call it to return the Attribute
	}

	// Broadcast initial Attribute Points
	AttributePointsChangedDelegate.Broadcast(GetAuraPS()->GetAttributePoints());
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	// Broadcast Attribute changes to Widgets
	check(AttributeInfo);

	for (auto& Pair : GetAuraAS()->TagsToAttributes) {
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data) 
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}

	// Bind callbacks to delegates related to Player State change
	// Bind callback to when the number of Attribute Points change
	GetAuraPS()->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 Points) {
			AttributePointsChangedDelegate.Broadcast(Points);
		}
	);
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	// Call the same function in ASC as it is the component responsible for Attributes
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	// GetNumericValue AttributeSet as argument because the Attribute/Attribute Value is returned from a static function 
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);

	// Broadcast to Widgets
	AttributeInfoDelegate.Broadcast(Info);
}
