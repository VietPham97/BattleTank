// Created by Pham Hoang Viet in 2021.


#include "TankBarrel.h"

void UTankBarrel::ElevateWithSpeed(float RelativeSpeed)
{
	// Rotate the Barrel the right amount each frame
	// Given the max elevation speed, and the time frame
	float NewRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	float ElevationChangePerFrame = NewRelativeSpeed * MaxDegreesPerSecond * DeltaTime;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChangePerFrame;
	float NewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(NewElevation, 0.0f, 0.0f));
}
