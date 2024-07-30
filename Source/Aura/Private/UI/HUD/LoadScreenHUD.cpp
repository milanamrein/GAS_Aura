// Copyright Milán Amrein


#include "UI/HUD/LoadScreenHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/LoadScreenWidget.h"
#include "UI/ViewModel/LoadScreenViewModel.h"

void ALoadScreenHUD::BeginPlay()
{
	Super::BeginPlay();

	// Create ViewModel
	LoadScreenViewModel = NewObject<ULoadScreenViewModel>(this, LoadScreenViewModelClass);
	LoadScreenViewModel->InitializeLoadSlots();
	
	// Create Load Screen Widget and add it to the Viewport
	LoadScreenWidget = CreateWidget<ULoadScreenWidget>(GetWorld(), LoadScreenWidgetClass);
	LoadScreenWidget->AddToViewport();
	LoadScreenWidget->BlueprintInitializeWidget();

	// Load Saved Game Data from disk
	LoadScreenViewModel->LoadData();
}
