// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LoadScreenHUD.generated.h"

class ULoadScreenWidget;
class ULoadScreenViewModel;

/**
 * HUD Class for the Load Screen
 */
UCLASS()
class AURA_API ALoadScreenHUD : public AHUD
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Class to create the Load Screen Widget from
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoadScreenWidgetClass;

	/// <summary>
	/// Load Screen Widget Pointer
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ULoadScreenWidget> LoadScreenWidget;

	/// <summary>
	/// Class to construct the ViewModel from
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULoadScreenViewModel> LoadScreenViewModelClass;

	/// <summary>
	/// Load Screen ViewModel Pointer
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ULoadScreenViewModel> LoadScreenViewModel;

protected:

	virtual void BeginPlay() override;

};
