// Created by Pham Hoang Viet in 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMotor.generated.h"

class ATank;
class UTankTrack;

/**
 * Responsible for driving the tank tracks.
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMotor : public UNavMovementComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = Speed)
	float MaxSpeedForward = 1000.0f; // 1m every frame

	UPROPERTY(EditDefaultsOnly, Category = Speed)
	float MaxSpeedTurning = 10.0f;

	ATank* OwningTank = nullptr;

public:
	void ForwardHandler(float ThrowValue);
	void TurningHandler(float ThrowValue);

	void SetOwningTank(ATank* TankPawn);

	bool IsOwningTank();

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
