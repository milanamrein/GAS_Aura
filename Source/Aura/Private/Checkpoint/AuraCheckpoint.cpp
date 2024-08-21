// Copyright Milán Amrein


#include "Checkpoint/AuraCheckpoint.h"
#include "Components/SphereComponent.h"
#include "Interaction/PlayerInterface.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AAuraCheckpoint::AAuraCheckpoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	// Setup Checkpoint Mesh
	CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>("CheckpointMesh");
	CheckpointMesh->SetupAttachment(GetRootComponent());
	CheckpointMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CheckpointMesh->SetCollisionResponseToAllChannels(ECR_Block);
	CheckpointMesh->SetCustomDepthStencilValue(CustomDepthStencilOverride);
	CheckpointMesh->MarkRenderStateDirty();

	// Setup Sphere
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(CheckpointMesh); // CheckpointMesh is going to be placed differently than the PlayerStart and we need the Sphere to move as well
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Setup MoveToComponent
	MoveToComponent = CreateDefaultSubobject<USceneComponent>("MoveToComponent");
	MoveToComponent->SetupAttachment(GetRootComponent());
}

void AAuraCheckpoint::LoadActor_Implementation()
{
	if (bReached) {
		HandleGlowEffects();
	}
}

void AAuraCheckpoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only overlap when the Actor is the Player
	if (OtherActor->Implements<UPlayerInterface>()) {
		bReached = true;
		// Save World state
		if (AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this))) {
			// Save current Map
			const UWorld* World = GetWorld();
			FString MapAssetName = World->GetMapName();
			MapAssetName.RemoveFromStart(World->StreamingLevelsPrefix);

			AuraGameMode->SaveWorldState(GetWorld(), MapAssetName);
		}

		// Save Player's progress
		IPlayerInterface::Execute_SaveProgress(OtherActor, PlayerStartTag);
		HandleGlowEffects();
	}
}

void AAuraCheckpoint::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraCheckpoint::OnSphereOverlap);
}

void AAuraCheckpoint::HighlightActor_Implementation()
{
	CheckpointMesh->SetRenderCustomDepth(true);
}

void AAuraCheckpoint::UnHighlightActor_Implementation()
{
	CheckpointMesh->SetRenderCustomDepth(false);
}

void AAuraCheckpoint::SetMoveToLocation_Implementation(FVector& OutDestination)
{
	OutDestination = MoveToComponent->GetComponentLocation();
}

void AAuraCheckpoint::HandleGlowEffects()
{
	// No collision while handling Checkpoint effects
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Create MI and set as the Material of the Mesh to show the glow effect
	UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(CheckpointMesh->GetMaterial(0), this);
	CheckpointMesh->SetMaterial(0, DynamicMaterialInstance);

	// Call BP Event
	CheckpointReached(DynamicMaterialInstance);
}
