// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadScreenWidget.generated.h"

/**
 * Base Widget class for Load Screen widgets
 */
UCLASS()
class AURA_API ULoadScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// BP Function to initialize this Load Screen Widget
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BlueprintInitializeWidget();

};
