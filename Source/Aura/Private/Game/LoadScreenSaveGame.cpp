// Copyright Milán Amrein


#include "Game/LoadScreenSaveGame.h"

FSavedMap ULoadScreenSaveGame::GetSavedMap(const FString& InMapName)
{
    for (const FSavedMap& Map : SavedMaps) {
        if (Map.MapAssetName.Equals(InMapName)) return Map;
    }

    return FSavedMap();
}

bool ULoadScreenSaveGame::HasMap(const FString& InMapName)
{
    for (const FSavedMap& Map : SavedMaps) {
        if (Map.MapAssetName.Equals(InMapName)) return true;
    }

    return false;
}
