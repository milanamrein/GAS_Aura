// Copyright Milán Amrein


#include "Actor/AuraProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Aura/Aura.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystemComponent.h"

AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	// Setup Sphere
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile); // set Object Type to custom channel
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Setup Movement component for Projectile
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);

	// Spawn Looping Sound when Projectile is instantiated
	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}

void AAuraProjectile::Destroyed()
{
	if (!bHit && !HasAuthority()) { // Destroyed() is called before OnSphereOverlap() on client
		// Spawn effects
		OnHit();
	}

	Super::Destroyed();
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* SourceAvatarActor = DamageEffectParams.SourceASC->GetAvatarActor();

	// Do not damage Self
	if (SourceAvatarActor == OtherActor) return;

	// Do not damage friends
	if (UAuraAbilitySystemLibrary::IsFriend(SourceAvatarActor, OtherActor)) return;

	if (!bHit) OnHit();	// Spawn effects on overlap

	// Destroy Projectile on server
	if (HasAuthority()) {
		// Set TargetASC & Apply Damage Gameplay Effect
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor)) {
			// Store the direction of the Projectile as the direction for the Death impulse
			const FVector DeathImpulse = GetActorForwardVector() * DamageEffectParams.DeathImpulseMagnitude;
			DamageEffectParams.DeathImpulse = DeathImpulse;

			// Calculate direction for successful Knockback
			const bool bKnockback = FMath::RandRange(1, 100) < DamageEffectParams.KnockbackChance.GetValueAtLevel(DamageEffectParams.AbilityLevel);
			if (bKnockback) {
				FRotator Rotation = GetActorRotation();
				Rotation.Pitch = 45.f;
				const FVector KnockbackDirection = Rotation.Vector();
				const FVector KnockbackForce = KnockbackDirection * DamageEffectParams.KnockbackForceMagnitude.GetValueAtLevel(DamageEffectParams.AbilityLevel);
				DamageEffectParams.KnockbackForce = KnockbackForce;
			}

			DamageEffectParams.TargetASC = TargetASC;
			UAuraAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
		}

		Destroy(); // this might happen before OnSphereOverlap on clients
	}
	else { // OnSphereOverlap was called before Projectile destruction on clients
		bHit = true;
	}
}

void AAuraProjectile::OnHit()
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	if (LoopingSoundComponent) LoopingSoundComponent->Stop();
	bHit = true;
}
