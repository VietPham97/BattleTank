// Created by Pham Hoang Viet in 2021.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	if (!LeftTrack || !RightTrack) return;
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::SetLeftTrackComponent(UTankTrack* Track)
{
	this->LeftTrack = Track;
}

void UTankMovementComponent::SetRightTrackComponent(UTankTrack* Track)
{
	this->RightTrack = Track;
}

