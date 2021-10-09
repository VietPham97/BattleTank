// Created by Pham Hoang Viet in 2021.


#include "TankMotor.h"
#include "TankTrack.h"
#include "Pawn/Tank.h"

void UTankMotor::ForwardHandler(float ThrowValue)
{
	if (!IsOwningTank()) { return; }

	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	float DistanceTravel = ThrowValue * MaxSpeedForward * DeltaTime;
	OwningTank->AddActorLocalOffset(FVector(DistanceTravel, 0.0f, 0.0f));
}

void UTankMotor::TurningHandler(float ThrowValue)
{
	if (!IsOwningTank()) { return; }

	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	float DegreeTurned = ThrowValue * MaxSpeedTurning * DeltaTime;
	OwningTank->AddActorLocalRotation(FRotator(0.0f, DegreeTurned, 0.0f));
}

void UTankMotor::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	if (!IsOwningTank()) { return; }

	FVector ForwardDirection = OwningTank->GetActorForwardVector().GetSafeNormal();
	FVector VelocityDirectionTowardPlayer = MoveVelocity.GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(VelocityDirectionTowardPlayer, ForwardDirection);
	ForwardHandler(ForwardThrow);
	
	float RightThrow = FVector::CrossProduct(ForwardDirection, VelocityDirectionTowardPlayer).Z;
	TurningHandler(RightThrow);
}

void UTankMotor::SetOwningTank(ATank* TankPawn)
{
	this->OwningTank = TankPawn;
}

bool UTankMotor::IsOwningTank()
{
	if (!OwningTank) {
		UE_LOG(LogTemp, Error, TEXT("No owner found on TankMotor"));
		return false;
	}

	return true;
}

