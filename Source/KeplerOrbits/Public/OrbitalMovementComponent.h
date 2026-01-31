#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OrbitalMovementComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class KEPLERORBITS_API UOrbitalMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOrbitalMovementComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// --- Physics Parameters ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbits")
	float Mass = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbits")
	FVector Velocity = FVector::ZeroVector;

	/** If true, this body won't be moved by gravity (the Sun) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbits")
	bool bIsFixedBody = false;

	/** Gravitational Constant - tweak this to see movement at UE scales */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbits")
	float GConstant = 100.0f;

private:
	USceneComponent* RootComp;
};