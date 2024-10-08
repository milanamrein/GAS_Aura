// Copyright Milán Amrein


#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ViewModel/LoadSlotViewModel.h"
#include "Game/LoadScreenSaveGame.h"
#include "GameFramework/PlayerStart.h"
#include "Game/AuraGameInstance.h"
#include "EngineUtils.h"
#include "Interaction/SaveInterface.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Aura/AuraLogChannels.h"
#include "GameFramework/Character.h"

void AAuraGameModeBase::SaveSlotData(ULoadSlotViewModel* LoadSlot, int32 SlotIndex)
{
	// Delete existing Save Slot to override
	DeleteSlot(LoadSlot->LoadSlotName, SlotIndex);
	

	// Create new Save
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
	LoadScreenSaveGame->PlayerName = LoadSlot->GetPlayerName();
	LoadScreenSaveGame->SaveSlotStatus = Taken;
	LoadScreenSaveGame->MapName = LoadSlot->GetMapName();
	LoadScreenSaveGame->MapAssetName = LoadSlot->MapAssetName;
	LoadScreenSaveGame->PlayerStartTag = LoadSlot->PlayerStartTag;

	// Save Game
	UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame, LoadSlot->LoadSlotName, SlotIndex);
}

ULoadScreenSaveGame* AAuraGameModeBase::GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const
{
	USaveGame* SavedGameObject = nullptr;
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex)) {
		SavedGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
	}
	else {
		SavedGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	}

	ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SavedGameObject);

	return LoadScreenSaveGame;
}

ULoadScreenSaveGame* AAuraGameModeBase::GetInGameSaveData() const
{
	if (UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance())) {
		return GetSaveSlotData(AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex);
	}

	return nullptr;
}

void AAuraGameModeBase::SaveInGameProgress(ULoadScreenSaveGame* SaveObject)
{
	if (UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance())) {
		AuraGameInstance->PlayerStartTag = SaveObject->PlayerStartTag;
		UGameplayStatics::SaveGameToSlot(SaveObject, AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex);
	}
}

void AAuraGameModeBase::SaveWorldState(UWorld* World, const FString& DestinationMapAssetName) const
{
	// Get actual MapAssetName
	FString WorldName = World->GetMapName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);

	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	check(AuraGameInstance);
	if (ULoadScreenSaveGame* SaveGame = GetSaveSlotData(AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex)) {
		if (!DestinationMapAssetName.IsEmpty()) { // Changing to a new World
			SaveGame->MapAssetName = DestinationMapAssetName;
			SaveGame->MapName = GetMapNameFromMapAssetName(DestinationMapAssetName);
		}

		if (!SaveGame->HasMap(WorldName)) {
			// Create new SavedMap if it doesn't exist already
			FSavedMap NewSavedMap;
			NewSavedMap.MapAssetName = WorldName;
			SaveGame->SavedMaps.Add(NewSavedMap);
		}

		// Set state of SavedMap
		FSavedMap SavedMap = SaveGame->GetSavedMap(WorldName);
		SavedMap.SavedActors.Empty(); // init array by emptying it

		// This could be optimized to only iterate through a set of Actors we want to save
		// but now it is iterating through all Actors in the World
		for (FActorIterator It(World); It; ++It) {
			AActor* Actor = *It;
			if (!IsValid(Actor) || !Actor->Implements<USaveInterface>()) continue;

			FSavedActor SavedActor;
			SavedActor.ActorName = Actor->GetFName();
			SavedActor.ActorTransform = Actor->GetTransform();

			// Serialize SaveGame UProperties to effectively save data
			FMemoryWriter MemoryWriter(SavedActor.Bytes);
			FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, true);
			Archive.ArIsSaveGame = true; // be compitable with a SaveGame object
			Actor->Serialize(Archive);
			SavedMap.SavedActors.AddUnique(SavedActor);
		}

		// Overwrite old data with new
		for (FSavedMap& MapToReplace : SaveGame->SavedMaps) {
			if (MapToReplace.MapAssetName.Equals(WorldName)) {
				MapToReplace = SavedMap;
			}
		}

		// Save Game
		UGameplayStatics::SaveGameToSlot(SaveGame, AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex);
	}
}

void AAuraGameModeBase::LoadWorldState(UWorld* World) const
{
	// Get actual MapAssetName
	FString WorldName = World->GetMapName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);

	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	check(AuraGameInstance);
	if (ULoadScreenSaveGame* SaveGame = GetSaveSlotData(AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex)) {
		// This could be optimized to only iterate through a set of Actors we want to save
		// but now it is iterating through all Actors in the World
		for (FActorIterator It(World); It; ++It) {
			AActor* Actor = *It;
			if (!Actor->Implements<USaveInterface>()) continue;

			for (FSavedActor SavedActor : SaveGame->GetSavedMap(WorldName).SavedActors) {
				if (SavedActor.ActorName.IsEqual(Actor->GetFName())) {
					if (ISaveInterface::Execute_IsMoveable(Actor)) {
						Actor->SetActorTransform(SavedActor.ActorTransform);
					}

					// Deserialize saved data
					FMemoryReader MemoryReader(SavedActor.Bytes);
					FObjectAndNameAsStringProxyArchive Archive(MemoryReader, true);
					Archive.ArIsSaveGame = true;
					Actor->Serialize(Archive); // converts binary bytes back into vars

					ISaveInterface::Execute_LoadActor(Actor);
				}
			}
		}
	}
	else {
		UE_LOG(LogAura, Error, TEXT("Failed to load Slot."));
		return;
	}
}

void AAuraGameModeBase::DeleteSlot(const FString& SlotName, int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex)) {
		UGameplayStatics::DeleteGameInSlot(SlotName, SlotIndex);
	}
}

void AAuraGameModeBase::TravelToMap(ULoadSlotViewModel* Slot)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(Slot, Maps.FindChecked(Slot->GetMapName()));
}

AActor* AAuraGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	if (UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance())) {
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Actors);
		if (Actors.Num() > 0) {
			AActor* SelectedActor = Actors[0];
			for (AActor* Actor : Actors) {
				if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor)) {
					if (PlayerStart->PlayerStartTag == AuraGameInstance->PlayerStartTag) {
						SelectedActor = PlayerStart;
						break;
					}
				}
			}

			return SelectedActor;
		}

		return nullptr;
	}
	
	return nullptr;
}

void AAuraGameModeBase::PlayerDied(ACharacter* DeadCharacter)
{
	ULoadScreenSaveGame* SaveGame = GetInGameSaveData();
	if (!IsValid(SaveGame)) return;

	// Load/Travel to last saved state of the game
	UGameplayStatics::OpenLevel(DeadCharacter, FName(SaveGame->MapAssetName));
}

void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Init default map
	Maps.Add(DefaultMapName, DefaultMap);
}

FString AAuraGameModeBase::GetMapNameFromMapAssetName(const FString& InMapAssetName) const
{
	for (auto& Map : Maps) {
		if (Map.Value.ToSoftObjectPath().GetAssetName().Equals(InMapAssetName)) {
			return Map.Key;
		}
	}

	return FString();
}
