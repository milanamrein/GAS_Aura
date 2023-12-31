// Copyright Milán Amrein


#include "AI/FindNearestPlayerBTService.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BTFunctionLibrary.h"

void UFindNearestPlayerBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Get Enemy pawn
	APawn* OwningPawn = AIOwner->GetPawn();

	// Get Player Characters if the Owner is an Enemy, but if it is a Player (e.g. friendly AI), then get Enemies
	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");
	TArray<AActor*> ActorsWithTag; // will be a single Actor in Single Player in the case of a Player
	UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, ActorsWithTag);

	// Find closest Actor
	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;
	for (AActor* Actor : ActorsWithTag) {
		if (IsValid(Actor) && IsValid(OwningPawn)) {
			const float Distance = OwningPawn->GetDistanceTo(Actor);
			if (Distance < ClosestDistance) {
				ClosestDistance = Distance;
				ClosestActor = Actor;
			}
		}
	}

	// Set Blackboard keys
	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollowSelector, ClosestActor);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetSelector, ClosestDistance);
}
