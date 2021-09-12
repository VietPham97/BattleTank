// Created by Pham Hoang Viet in 2021.


#include "TankAimingComponent.h"
#include "Components/SceneComponent.h"
#include "Component/TankTurret.h"
#include "Component/TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetTurretComponent(UTankTurret* Turret)
{
	this->TurretComponent = Turret;
}

void UTankAimingComponent::SetBarrelComponent(UTankBarrel* Barrel)
{
	this->BarrelComponent = Barrel;
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float LaunchSpeed)
{
	if (!TurretComponent && !BarrelComponent) { 
		return; 
	}

	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = BarrelComponent->GetSocketLocation(FName("Projectile"));

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

void UTankAimingComponent::RotateTurretToward(const FVector& AimDirection)
{
	FRotator CurrentRotation = TurretComponent->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - CurrentRotation;

	TurretComponent->RotateWithSpeed(DeltaRotation.Yaw);
}

void UTankAimingComponent::RotateBarrelToward(const FVector& AimDirection)
{
	// Calculate the difference between current barrel rotation, and AimDirection
	FRotator CurrentRotation = BarrelComponent->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - CurrentRotation;

	BarrelComponent->ElevateWithSpeed(DeltaRotation.Pitch);
}

