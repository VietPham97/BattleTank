// Created by Pham Hoang Viet in 2021.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::MoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO: Prevent double speed due to dual controller
}

void UTankMovementComponent::TurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	// TODO: Prevent double speed due to dual controller
}

void UTankMovementComponent::SetLeftTrackComponent(UTankTrack* Track)
{
	this->LeftTrack = Track;
}

void UTankMovementComponent::SetRightTrackComponent(UTankTrack* Track)
{
	this->RightTrack = Track;
}

