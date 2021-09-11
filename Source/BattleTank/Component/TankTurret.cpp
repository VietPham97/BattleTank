// Created by Pham Hoang Viet in 2021.


#include "TankTurret.h"

void UTankTurret::RotateWithSpeed(float RelativeSpeed)
{
	// Rotate the Turret the right amount each frame
	// Given the max elevation speed, and the time frame
	float NewRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	float RotationChangePerFrame = NewRelativeSpeed * MaxDegreesPerSecond * DeltaTime;
	float NewRotation = GetRelativeRotation().Yaw + RotationChangePerFrame;
	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
}
