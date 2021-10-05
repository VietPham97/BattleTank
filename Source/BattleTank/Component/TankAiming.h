// Created by Pham Hoang Viet in 2021.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAiming.generated.h"

class UTankTurret;
class UTankBarrel;

/**
 * Responsible for rotating the tank turret and barrel.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAiming : public UActorComponent
{
	GENERATED_BODY()

private:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;

public:	
	// Sets default values for this component's properties
	UTankAiming();

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* Turret, UTankBarrel* Barrel);

	void AimAt(FVector TargetLocation, float LaunchSpeed);

private:
	void RotateTurretToward(const FVector& AimDirection);
	void RotateBarrelToward(const FVector& AimDirection);
};
