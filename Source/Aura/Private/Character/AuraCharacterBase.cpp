// Copyright Milán Amrein


#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Aura/Aura.h"
#include "AuraGameplayTags.h"
#include "Kismet/GameplayStatics.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false); // designate Overlap events to be on the Mesh only
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap); // Overlap with custom Projectile channel (Aura & Enemies)
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

FVector AAuraCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	// Get Socket Location on Weapon
	if (MontageTag.MatchesTagExact(FAuraGameplayTags::Get().CombatSocket_Weapon) && IsValid(Weapon)) {
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	// Get Socket Location on Left Hand
	if (MontageTag.MatchesTagExact(FAuraGameplayTags::Get().CombatSocket_LeftHand)) {
		return GetMesh()->GetSocketLocation(LeftHandTipSocketName);
	}
	// Get Socket Location on Right Hand
	if (MontageTag.MatchesTagExact(FAuraGameplayTags::Get().CombatSocket_RightHand)) {
		return GetMesh()->GetSocketLocation(RightHandTipSocketName);
	}
	// Get Socket Location on Tail
	if (MontageTag.MatchesTagExact(FAuraGameplayTags::Get().CombatSocket_Tail)) {
		return GetMesh()->GetSocketLocation(TailSocketName);
	}

	return FVector();
}

bool AAuraCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* AAuraCharacterBase::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> AAuraCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

UNiagaraSystem* AAuraCharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

FTaggedMontage AAuraCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage : AttackMontages) {
		if (TaggedMontage.MontageTag.MatchesTagExact(MontageTag)) return TaggedMontage;
	}

	return FTaggedMontage();
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this); // needed for applying effect to Self and for MMC
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f); // Need to be applied after Secondary because of MaxHealth and MaxMana
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	// Abilities must be granted and granted only on the server
	if (!HasAuthority()) return;

	// Granting abilities is the responsibility of the AbilitySystemComponent
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->AddCharacterAbilities(StartupAbilities);
}

void AAuraCharacterBase::Dissolve()
{
	// Character dissolve
	if (!IsValid(DissolveMaterialInstance)) return;
	UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
	GetMesh()->SetMaterial(0, DynamicMatInst); // would need to do this for all materials if we had more

	StartDissolveTimeline(DynamicMatInst);

	// Weapon dissolve
	if (!IsValid(WeaponDissolveMaterialInstance)) return;
	DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
	Weapon->SetMaterial(0, DynamicMatInst);

	StartWeaponDissolveTimeline(DynamicMatInst); // can't use the same timeline for both dissolve effect
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AAuraCharacterBase::Die()
{
	// Drop weapon
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true)); // automatically replicates

	MulticastHandleDeath();
}

void AAuraCharacterBase::MulticastHandleDeath_Implementation()
{
	// Play Death Sound
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());

	// Simulate Physics for Character death (ragdoll)
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block); // collide with walls, floor etc.

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); // will not block other objects from passing through the "dead"
	Dissolve();
	bDead = true;
}
