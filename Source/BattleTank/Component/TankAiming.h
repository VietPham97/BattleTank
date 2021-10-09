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
class AProjectile;

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

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f; // 40 m/s ~ 4,000 cm/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	double LastFireTime = 0;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileObject;

public:	
	// Sets default values for this component's properties
	UTankAiming();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* Turret, UTankBarrel* Barrel);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:
	void RotateBarrelToward(const FVector& AimDirection);
};
