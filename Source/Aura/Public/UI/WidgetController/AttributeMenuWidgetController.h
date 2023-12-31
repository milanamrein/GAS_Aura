// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AttributeMenuWidgetController.generated.h"

struct FGameplayAttribute;

// Delegate signature for broadcasting an AuraAttributeInfo struct
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

/**
 * Widget Controller class for the Attribute Menu
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	/// <summary>
	/// Delegate for broadcasting Attribute information
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:

	/// <summary>
	/// Function to execute the broadcast of the Attribute Information
	/// </summary>
	/// <param name="AttributeTag">Gameplay Tag needed for the broadcast</param>
	/// <param name="Attribute">Attribute to broadcast</param>
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;

};
