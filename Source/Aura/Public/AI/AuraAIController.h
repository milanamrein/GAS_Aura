// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AuraAIController.generated.h"

class UBehaviorTreeComponent;

/**
 * AI Controller class for Enemies
 */
UCLASS()
class AURA_API AAuraAIController : public AAIController
{
	GENERATED_BODY()

public:

	AAuraAIController();

protected:
	
	/// <summary>
	/// Component storing BehaviorTree used by AIController
	/// </summary>
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
