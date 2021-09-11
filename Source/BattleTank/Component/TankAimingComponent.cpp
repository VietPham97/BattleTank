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
	if (!this->TurretComponent && !this->BarrelComponent) { 
		return; 
	}

	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = this->BarrelComponent->GetSocketLocation(FName("Projectile"));

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
	FRotator CurrentRotation = this->TurretComponent->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - CurrentRotation;

	this->TurretComponent->RotateWithSpeed(DeltaRotation.Yaw);
}

void UTankAimingComponent::RotateBarrelToward(const FVector& AimDirection)
{
	// Calculate the difference between current barrel rotation, and AimDirection
	FRotator CurrentRotation = this->BarrelComponent->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - CurrentRotation;

	this->BarrelComponent->ElevateWithSpeed(DeltaRotation.Pitch);
}

