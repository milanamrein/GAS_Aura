// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AttributeMenuWidgetController.generated.h"

struct FGameplayAttribute;
struct FGameplayTag;

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

	/// <summary>
	/// Delegate for broadcasint Attribute Points changing
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnPlayerStatChangedSignature AttributePointsChangedDelegate;

	/// <summary>
	/// Function to upgrade an Attribute using Attribute Points
	/// </summary>
	/// <param name="AttributeTag">Tag of the Attribute that is going to be upgraded</param>
	UFUNCTION(BlueprintCallable)
	void UpgradeAttribute(const FGameplayTag& AttributeTag);

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
