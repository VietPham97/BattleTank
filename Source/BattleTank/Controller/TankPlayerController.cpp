// Created by Pham Hoang Viet in 2021.


#include "TankPlayerController.h"
#include "Component/TankAiming.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto TankAiming = GetPawn()->FindComponentByClass<UTankAiming>();
	if (!ensure(TankAiming)) { return; }

	FVector HitLocation; // out parameter
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		TankAiming->AimAt(HitLocation);
	}
}

// Get World location if linetrace through crosshair, return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line trace along that aim direction, and see what hits
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraToWorldLocation; // TODO: Discard this variable
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraToWorldLocation, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	bool LineTraceSuccess = GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLocation, 
		EndLocation, 
		ECollisionChannel::ECC_Visibility
	);
	
	OutHitLocation = LineTraceSuccess ? HitResult.Location : FVector(0.0f);
	return LineTraceSuccess;
}

