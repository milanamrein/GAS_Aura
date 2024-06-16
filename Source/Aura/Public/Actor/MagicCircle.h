// Copyright Milán Amrein

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicCircle.generated.h"

/**
* Decal Actor for Aura's Magic Circle
*/
UCLASS()
class AURA_API AMagicCircle : public AActor
{
	GENERATED_BODY()
	
public:	
	AMagicCircle();
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Decal Component for the Magic Circle
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDecalComponent> MagicCircleDecal;

protected:
	virtual void BeginPlay() override;
};
