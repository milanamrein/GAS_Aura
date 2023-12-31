// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "FindNearestPlayerBTService.generated.h"

/**
 * Behavior Tree Service used by Enemies to find the nearest Player Character and start to pursue them
 */
UCLASS()
class AURA_API UFindNearestPlayerBTService : public UBTService_BlueprintBase
{
	GENERATED_BODY()
	
protected:

	// Function where we can specify how frequently execute the BT node
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/// <summary>
	/// TargetToFollow Selector that allows us to create a link between this C++ class
	/// and any of our keys on the Blackboard
	/// </summary>
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector TargetToFollowSelector;

	/// <summary>
	/// DistanceToTarget Selector that allows us to create a link between this C++ class
	/// and our key on the Blackboard
	/// </summary>
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector DistanceToTargetSelector;
};
