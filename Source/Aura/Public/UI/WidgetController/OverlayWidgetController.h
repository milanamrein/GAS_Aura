// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
class UAuraUserWidget;
class UAuraAbilitySystemComponent;

// DataTableRow struct for storing information that gets broadcasted to UI Widgets
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	/// <summary>
	/// GameplayTag of the message
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	/// <summary>
	/// Message to display on the UI
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	/// <summary>
	/// Widget to create and add to the viewport
	/// whenever we receive this Tag in the form
	/// of a GameplayEffect
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	
	/// <summary>
	/// Optional Image to show alongside the Message
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

//~ Begin Delegate signatures

// Delegate type to broadcast Attribute values
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
// Delegate type to broadcast a UI Widget Row
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

//~ End Delegate signatures

/**
 * Widget Controller for the Overlay
 */
UCLASS(BlueprintType, Blueprintable) // We can access it in BP Event Graph and we can create a BP from it
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	//~ Begin Delegates

	// We bind these delegates in BP
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	// We bind these delegates in BP
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	/// <summary>
	/// Delegate for broadcasting a UI Widget Row.
	/// Can bind this delegate to the Widget BP
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

	/// <summary>
	/// Delegate for broadcasting when the percent of
	/// the XP bar has changed. Technically it is not an
	/// Attribute, but the same delegate signature can be
	/// used.
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "GAS|XP")
	FOnAttributeChangedSignature OnXPPercentChangedDelegate;

	/// <summary>
	/// Delegate for broadcasting when a Player Stat is changed
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "GAS|Level")
	FOnPlayerStatChangedSignature OnPlayerLevelChangedDelegate;

	//~ End Delegates

protected:

	/// <summary>
	/// DataTable for storing FUIWidgetRow structs
	/// that get broadcasted to UI Widgets
	/// </summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	/// <summary>
	/// Template function that returns a DataTable Row
	/// by a DataTable and GameplayTag
	/// </summary>
	/// <param name="DataTable">Data Table</param>
	/// <param name="Tag">Gameplay Tag</param>
	/// <returns>DataTable Row</returns>
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

	/// <summary>
	/// Callback function to when the amount of XP changes
	/// </summary>
	/// <param name="NewXP">New XP Amount</param>
	UFUNCTION()
	void OnXPChanged(int32 NewXP);

	/// <summary>
	/// Callback function to when an Ability is equipped
	/// </summary>
	void OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot) const;
};

template<typename T>
inline T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
