// Copyright Milán Amrein


#include "AbilitySystem/Abilities/AuraBeamSpell.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult)
{
	if (HitResult.bBlockingHit) {
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor = HitResult.GetActor();
	}
	else { // we didn't hit anything
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void UAuraBeamSpell::StoreOwner()
{
	if (CurrentActorInfo) {
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
	}
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation, const FName& BeamStartSocket)
{
	// Do a Sphere Trace to allow some leeway
	check(OwnerCharacter);
	if (!OwnerCharacter->Implements<UCombatInterface>()) return;
	if (USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter)) {
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(OwnerCharacter);
		FHitResult HitResult;
		const FVector SocketLocation = Weapon->GetSocketLocation(BeamStartSocket);

		UKismetSystemLibrary::SphereTraceSingle(
			OwnerCharacter,
			SocketLocation,
			BeamTargetLocation,
			10.f,
			TraceTypeQuery1,
			false,
			ActorsToIgnore,
			EDrawDebugTrace::None,
			HitResult,
			true
		);

		if (HitResult.bBlockingHit) { // if we hit something between the Start and the original BeamTarget
			MouseHitLocation = HitResult.ImpactPoint;
			MouseHitActor = HitResult.GetActor();
		}
	}

	// Bind Die delegates for Primary Target
	if (ICombatInterface* CombatActor = Cast<ICombatInterface>(MouseHitActor)) {
		if (!CombatActor->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::PrimaryTargetDied)) {
			CombatActor->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::PrimaryTargetDied);
		}
	}
}

void UAuraBeamSpell::StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo()); // Ignore Aura
	ActorsToIgnore.Add(MouseHitActor); // Ignore Mouse Hit Target
	
	TArray<AActor*> OverlappingActors;
	UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(
		GetAvatarActorFromActorInfo(),
		OverlappingActors,
		ActorsToIgnore,
		BeamRadius.GetValueAtLevel(GetAbilityLevel()),
		MouseHitActor->GetActorLocation()
	);

	// Get the closest bunch
	int32 NumAdditionalTargets = FMath::Min(GetAbilityLevel() - 1, MaxTargets);
	UAuraAbilitySystemLibrary::GetClosestTargets(
		NumAdditionalTargets, 
		OverlappingActors, 
		OutAdditionalTargets, 
		MouseHitActor->GetActorLocation()
	);

	// Bind Die delegates for Additional Targets
	for (AActor* Target : OutAdditionalTargets) {
		if (ICombatInterface* CombatActor = Cast<ICombatInterface>(MouseHitActor)) {
			if (!CombatActor->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::AdditionalTargetDied)) {
				CombatActor->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::AdditionalTargetDied);
			}
		}
	}
}
