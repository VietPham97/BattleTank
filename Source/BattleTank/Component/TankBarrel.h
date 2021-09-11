// Created by Pham Hoang Viet in 2021.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0.0f;
	
public:
	// RelativeSpeed: -1 is max downward speed, +1 is max up movement
	void ElevateWithSpeed(float RelativeSpeed);
};
