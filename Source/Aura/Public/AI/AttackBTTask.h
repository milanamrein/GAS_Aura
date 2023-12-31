// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "AttackBTTask.generated.h"

/**
 * Behavior Tree Task class for Attacking
 */
UCLASS()
class AURA_API UAttackBTTask : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
