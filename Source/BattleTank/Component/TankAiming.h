// Created by Pham Hoang Viet in 2021.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAiming.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading UMETA(DisplayName = "Reloading"),
	Aiming UMETA(DisplayName = "Aiming"),
	Locked UMETA(DisplayName = "Locked")
};

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
	
	EFiringState FiringState = EFiringState::Reloading;

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
