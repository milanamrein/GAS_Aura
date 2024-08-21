// Copyright Milán Amrein


#include "Checkpoint/AuraMapEntrance.h"
#include "Interaction/PlayerInterface.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

AAuraMapEntrance::AAuraMapEntrance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Sphere->SetupAttachment(MoveToComponent);
}

void AAuraMapEntrance::LoadActor_Implementation()
{
	// Do nothing when loading a Map Entrance
}

void AAuraMapEntrance::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only overlap when the Actor is the Player
	if (OtherActor->Implements<UPlayerInterface>()) {
		bReached = true;
		// Save World state
		if (AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this))) {
			AuraGameMode->SaveWorldState(GetWorld(), DestinationMap.ToSoftObjectPath().GetAssetName());
		}

		// Save Player's progress
		IPlayerInterface::Execute_SaveProgress(OtherActor, DestinationPlayerStartTag);

		// Travel to destination Map
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, DestinationMap);
	}
}
