// Copyright Milán Amrein


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);

	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// Initialize Native Gameplay Tags for the game
	FAuraGameplayTags::InitializeNativeGameplayTags();

	// Initialize Global Data (Target Data etc.); required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
