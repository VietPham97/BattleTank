// Created by Pham Hoang Viet in 2021.


#include "TankMotor.h"
#include "TankTrack.h"

void UTankMotor::ForwardHandler(float AxisValue)
{
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (!OwningPawn) { 
		UE_LOG(LogTemp, Error, TEXT("No owner found on TankMotor"));
		return; 
	}

	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	float DistanceTravel = AxisValue * MaxSpeedForward * DeltaTime;
	OwningPawn->AddActorLocalOffset(FVector(DistanceTravel, 0.0f, 0.0f));
}

void UTankMotor::TurningHandler(float AxisValue)
{
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (!OwningPawn) {
		UE_LOG(LogTemp, Error, TEXT("No owner found on TankMotor"));
		return;
	}

	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	float DegreeTurned = AxisValue * MaxSpeedTurning * DeltaTime;
	OwningPawn->AddActorLocalRotation(FRotator(0.0f, DegreeTurned, 0.0f));
}

void UTankMotor::SetLeftTrackComponent(UTankTrack* Track)
{
	this->LeftTrack = Track;
}

void UTankMotor::SetRightTrackComponent(UTankTrack* Track)
{
	this->RightTrack = Track;
}

