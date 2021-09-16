// Created by Pham Hoang Viet in 2021.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// TODO: Clamp throttle value so player can't over-drive
	FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForcePerTrack;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

