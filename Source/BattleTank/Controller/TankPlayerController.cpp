// Created by Pham Hoang Viet in 2021.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Pawn/Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->Tank = GetControlledTank();
	if (!this->Tank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing any Tank"));
	}
	else
	{
		FString TankName = this->Tank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *TankName);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!this->Tank) { return; }

	FVector HitLocation; // out parameter
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		AimTowardCrosshair(HitLocation);
	}
}

void ATankPlayerController::AimTowardCrosshair(FVector HitLocation) const
{
	UE_LOG(LogTemp, Warning, TEXT("Hitting at: %s"), *HitLocation.ToString());
	// TODO: Tell the controlled tank to aim at this point
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

	if (LineTraceSuccess)
	{
		OutHitLocation = HitResult.Location;
	}

	return LineTraceSuccess;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
