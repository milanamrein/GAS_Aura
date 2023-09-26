// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * HUD class
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Overlay Widget to add to the Viewport
	/// </summary>
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	/// <summary>
	/// Getter for OverlayWidgetController
	/// </summary>
	/// <param name="WCParams">WidgetController Params</param>
	/// <returns>OverlayWidgetController singleton</returns>
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	/// <summary>
	/// Function to initialize the Overlay (Widget & WidgetController)
	/// </summary>
	/// <param name="PC">PlayerController</param>
	/// <param name="PS">PlayerState</param>
	/// <param name="ASC">AbilitySystemComponent</param>
	/// <param name="AS">AttributeSet</param>
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:

	/// <summary>
	/// Class to create the Overlay Widget from
	/// </summary>
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	/// <summary>
	/// Overlay WidgetController
	/// </summary>
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	/// <summary>
	/// Class to create the Overlay ControllerWidget from
	/// </summary>
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
