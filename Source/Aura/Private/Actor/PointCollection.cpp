// Copyright Milán Amrein


#include "Actor/PointCollection.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

APointCollection::APointCollection()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Point Collection
	for (int32 i = 0; i < MaxNumOfPoints; i++) {
		USceneComponent* Point = CreateDefaultSubobject<USceneComponent>(FName(FString::Printf(TEXT("Pt_%d"), i)));
		Points.Add(Point);
		if (i == 0) {
			SetRootComponent(Point);
		}
		else {
			Point->SetupAttachment(GetRootComponent());
		}
	}
}

TArray<USceneComponent*> APointCollection::GetGroundPoints(const FVector& GroundLocation, int32 NumPoints, float YawOverride)
{
	checkf(NumPoints <= MaxNumOfPoints, TEXT("Attepmted to access Points array out of bounds."));

	// Create copy of Points
	TArray<USceneComponent*> PointsCopy;
	for (USceneComponent* Point : Points) {
		if (PointsCopy.Num() >= NumPoints) return PointsCopy; // return filled up array according to number of allowed Points

		if (Point != Points[0]) {
			// Reposition Point by rotating away from center Point (Point0) by YawOverride
			FVector ToPoint = Point->GetComponentLocation() - Points[0]->GetComponentLocation();
			ToPoint = ToPoint.RotateAngleAxis(YawOverride, FVector::UpVector);
			Point->SetWorldLocation(Points[0]->GetComponentLocation() + ToPoint);
		}

		// LineTrace to the Floor to get Ground Location
		const FVector RaisedLocation = FVector(
			Point->GetComponentLocation().X, 
			Point->GetComponentLocation().Y, 
			Point->GetComponentLocation().Z + 500.f
		); // Trace Start
		const FVector LoweredLocation = FVector(
			Point->GetComponentLocation().X,
			Point->GetComponentLocation().Y,
			Point->GetComponentLocation().Z - 500.f
		); // Trace End

		// Line Trace by Profile
		FHitResult HitResult;
		TArray<AActor*> IgnoreActors; // we want to ignore all Actors when line tracing
		UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(this, IgnoreActors, TArray<AActor*>(), 1500.f, GetActorLocation());
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActors(IgnoreActors);
		GetWorld()->LineTraceSingleByProfile(HitResult, RaisedLocation, LoweredLocation, FName("BlockAll"), QueryParams);

		// Adjust Location to HitResult ImpactPoint
		const FVector AdjustedLocation = FVector(
			Point->GetComponentLocation().X,
			Point->GetComponentLocation().Y,
			HitResult.ImpactPoint.Z
		);
		Point->SetWorldLocation(AdjustedLocation);
		Point->SetWorldRotation(UKismetMathLibrary::MakeRotFromZ(HitResult.ImpactNormal));

		PointsCopy.Add(Point);
	}

	return PointsCopy;
}

void APointCollection::BeginPlay()
{
	Super::BeginPlay();
	
}
