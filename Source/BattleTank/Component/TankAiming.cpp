// Created by Pham Hoang Viet in 2021.


#include "TankAiming.h"
#include "Components/SceneComponent.h"
#include "Component/TankTurret.h"
#include "Component/TankBarrel.h"
#include "Actor/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UTankAiming::UTankAiming()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}
\
void UTankAiming::Initialize(UTankTurret* Turret, UTankBarrel* Barrel)
{
	this->Turret = Turret;
	this->Barrel = Barrel;
}

void UTankAiming::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (!bHaveAimSolution) { 
		return; 
	}

	FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
	RotateBarrelToward(AimDirection);
}

void UTankAiming::RotateBarrelToward(const FVector& AimDirection)
{
	if (!ensure(Turret && Barrel)) { return; }

	// Calculate the difference between current barrel rotation, and AimDirection
	FRotator CurrentRotation = Barrel->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - CurrentRotation;

	Turret->RotateWithSpeed(DeltaRotation.Yaw);
	Barrel->ElevateWithSpeed(DeltaRotation.Pitch);
}

void UTankAiming::Fire()
{
	if (!ensure(Barrel && ProjectileObject)) { return; }
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!bIsReloaded) { return; }

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileObject,
		Barrel->GetSocketLocation("Projectile"),
		Barrel->GetSocketRotation("Projectile")
	);

	Projectile->LaunchWithSpeed(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}

