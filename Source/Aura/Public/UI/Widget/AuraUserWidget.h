// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * Base User Widget class
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Function for setting the Widget Controller
	/// on the Widget Blueprint
	/// </summary>
	/// <param name="InWidgetController"></param>
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	/// <summary>
	/// Function to handle UI functionalities once the WidgetController is set
	/// on the Widget Blueprint
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
