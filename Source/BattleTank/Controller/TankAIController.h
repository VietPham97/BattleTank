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
	class APawn* PlayerTank = nullptr;
	class APawn* ControlledTank = nullptr;
	
	class UTankAiming* TankAiming = nullptr;

protected:
	// The closest distance an ai can be to the player in centimeters
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000.0f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void LocatePlayerTank();
	
};
