// Copyright Milán Amrein


#include "AbilitySystem/Data/LootTiers.h"

TArray<FLootItem> ULootTiers::GetLootItems()
{
	TArray<FLootItem> Items;

	for (FLootItem& Item : LootItems) {
		for (int32 i = 0; i < Item.MaxNum; i++) {
			if (FMath::FRandRange(1.f, 100.f) < Item.Chance) {
				FLootItem NewItem;
				NewItem.LootClass = Item.LootClass;
				NewItem.bLootLevelOverride = Item.bLootLevelOverride;
				Items.Add(NewItem);
			}
		}
	}

	return Items;
}
