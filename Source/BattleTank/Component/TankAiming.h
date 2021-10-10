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

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000.0f; // 80 m/s ~ 8,000 cm/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	double LastFireTime = 0;

	FVector AimDirection;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileObject;

	UPROPERTY(BlueprintReadOnly, Category = "FiringState")
	EFiringState FiringState = EFiringState::Reloading;

public:	
	// Sets default values for this component's properties
	UTankAiming();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* Turret, UTankBarrel* Barrel);

	EFiringState GetFiringState() const;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:
	void RotateBarrelToward(const FVector& AimDirection);

	bool IsBarrelMoving();
};
