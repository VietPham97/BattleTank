// Created by Pham Hoang Viet in 2021.


#include "TankAiming.h"
#include "Components/SceneComponent.h"
#include "Component/TankTurret.h"
#include "Component/TankBarrel.h"
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

void UTankAiming::AimAt(FVector TargetLocation, float LaunchSpeed)
{
	if (!Turret && !Barrel) { 
		return; 
	}

	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		TargetLocation,
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
	RotateTurretToward(AimDirection);
	RotateBarrelToward(AimDirection);
}

void UTankAiming::RotateTurretToward(const FVector& AimDirection)
{
	FRotator CurrentRotation = Turret->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - CurrentRotation;

	Turret->RotateWithSpeed(DeltaRotation.Yaw);
}

void UTankAiming::RotateBarrelToward(const FVector& AimDirection)
{
	// Calculate the difference between current barrel rotation, and AimDirection
	FRotator CurrentRotation = Barrel->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - CurrentRotation;

	Barrel->ElevateWithSpeed(DeltaRotation.Pitch);
}

