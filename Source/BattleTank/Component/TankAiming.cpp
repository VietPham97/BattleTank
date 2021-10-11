// Created by Pham Hoang Viet in 2021.


#include "TankAiming.h"
#include "Components/SceneComponent.h"
#include "Component/TankTurret.h"
#include "Component/TankBarrel.h"
#include "Projectile/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UTankAiming::UTankAiming()
{
	PrimaryComponentTick.bCanEverTick = true;

	AimDirection = FVector::ZeroVector;
}

void UTankAiming::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}

void UTankAiming::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAiming::Initialize(UTankTurret* Turret, UTankBarrel* Barrel)
{
	this->Turret = Turret;
	this->Barrel = Barrel;
}

EFiringState UTankAiming::GetFiringState() const
{
	return FiringState;
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

	if (!bHaveAimSolution) { return; }

	AimDirection = OutLaunchVelocity.GetSafeNormal();
	RotateBarrelToward(AimDirection);
}

void UTankAiming::RotateBarrelToward(const FVector& AimDirection)
{
	if (!ensure(Turret && Barrel)) { return; }

	// Calculate the difference between current barrel rotation, and AimDirection
	FRotator CurrentRotation = Barrel->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator DeltaRotation = TargetRotation - CurrentRotation;

	auto TurretRotationAngle = (FMath::Abs(DeltaRotation.Yaw) < 180) ? DeltaRotation.Yaw : -DeltaRotation.Yaw;
	Turret->RotateWithSpeed(TurretRotationAngle);
	Barrel->ElevateWithSpeed(DeltaRotation.Pitch);
}

bool UTankAiming::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAiming::Fire()
{
	if (FiringState == EFiringState::Reloading) { return; }

	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileObject)) { return; }

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileObject,
		Barrel->GetSocketLocation("Projectile"),
		Barrel->GetSocketRotation("Projectile")
	);

	Projectile->LaunchWithSpeed(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}

