// Copyright Milán Amrein


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching) {
		// if we reach maximum Level, return
		// LevelUpInformation[0] is just a placeholder, LevelUpInformation[1] holds information on Level 1
		if (LevelUpInformation.Num() - 1 <= Level) return Level; 

		if (XP >= LevelUpInformation[Level].LevelUpRequirement) {
			// if XP is more/equal than the requirement for the current Level in check, then check next Level
			++Level;
		}
		else {
			// XP is not enough for requirement, stop search and return current Level
			bSearching = false;
		}
	}

	return Level;
}
