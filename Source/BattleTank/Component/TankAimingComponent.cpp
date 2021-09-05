// Created by Pham Hoang Viet in 2021.


#include "TankAimingComponent.h"
#include "Components/SceneComponent.h"
#include "Component/TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetTurretComponent(UStaticMeshComponent* TurretComponent)
{
	this->TurretComponent = TurretComponent;
}

void UTankAimingComponent::SetBarrelComponent(UTankBarrel* Barrel)
{
	this->BarrelComponent = Barrel;
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float LaunchSpeed)
{
	if (!this->BarrelComponent) { return; }

	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = this->BarrelComponent->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		TargetLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (!bHaveAimSolution) { return; }

	FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
	//FString TankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *TankName, *AimDirection.ToString());
	RotateBarrelToward(AimDirection);
}

void UTankAimingComponent::RotateBarrelToward(const FVector& AimDirection)
{
	// Calculate the difference between current barrel rotation, and AimDirection
	FRotator CurrentRotation = this->BarrelComponent->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - CurrentRotation;

	this->BarrelComponent->ElevateDegreesPerSecond(5); // TODO: Remove magic number
}

