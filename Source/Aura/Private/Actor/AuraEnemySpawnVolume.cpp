// Copyright Milán Amrein


#include "Actor/AuraEnemySpawnVolume.h"
#include "Actor/AuraEnemySpawnPoint.h"
#include "Components/BoxComponent.h"
#include "Interaction/PlayerInterface.h"

AAuraEnemySpawnVolume::AAuraEnemySpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	// Initialize Box
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionObjectType(ECC_WorldStatic);
	Box->SetCollisionResponseToAllChannels(ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}	

void AAuraEnemySpawnVolume::LoadActor_Implementation()
{
	// we don't need this volume the next time we load in as it has already been reached
	if (bReached) {
		Destroy();
	}
}

void AAuraEnemySpawnVolume::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	bReached = true;
	for (AAuraEnemySpawnPoint* Point : SpawnPoints) {
		if (IsValid(Point)) {
			Point->SpawnEnemy();
		}
	}

	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision); // do not destroy yet in order to save its state
}

void AAuraEnemySpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AAuraEnemySpawnVolume::OnBoxOverlap);
}
