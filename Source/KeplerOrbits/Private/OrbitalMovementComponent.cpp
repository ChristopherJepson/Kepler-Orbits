#include "DrawDebugHelpers.h"
#include "OrbitalMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UOrbitalMovementComponent::UOrbitalMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOrbitalMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	RootComp = GetOwner()->FindComponentByClass<USceneComponent>();
}

void UOrbitalMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!RootComp || bIsFixedBody) return;

	FVector CurrentLocation = RootComp->GetComponentLocation();
	FVector TotalAcceleration = FVector::ZeroVector;

	// Find all other orbital bodies
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("OrbitalBody"), FoundActors);

	for (AActor* OtherActor : FoundActors)
	{
		if (OtherActor == GetOwner()) continue;

		UOrbitalMovementComponent* OtherComp = OtherActor->FindComponentByClass<UOrbitalMovementComponent>();
		if (OtherComp)
		{
			FVector Dir = OtherComp->GetOwner()->GetActorLocation() - CurrentLocation;
			float DistanceSquared = Dir.SizeSquared();

			// Avoid division by zero
			if (DistanceSquared > 100.0f)
			{
				float AccelMagnitude = (GConstant * OtherComp->Mass) / DistanceSquared;
				TotalAcceleration += Dir.GetSafeNormal() * AccelMagnitude;

				// --- STEP 2: DRAW THE DEBUG LINE ---
				// We draw from the Planet (CurrentLocation) to the Star (OtherActor location)
				DrawDebugLine(GetWorld(), CurrentLocation, OtherActor->GetActorLocation(), FColor::Red, false, 0.1f, 0, 1.0f);
			}
		}
	}

	// Simple Euler Integration
	Velocity += TotalAcceleration * DeltaTime;
	FVector NewLocation = CurrentLocation + (Velocity * DeltaTime);
	GetOwner()->SetActorLocation(NewLocation);
}