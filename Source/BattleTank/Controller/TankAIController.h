// Created by Pham Hoang Viet in 2021.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	// The closest distance an ai can be to the player in centimeters
	float AcceptanceRadius = 3000.0f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void LocatePlayerTank();
	
};
