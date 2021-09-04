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
	class ATank* Tank = nullptr;
	class ATank* PlayerTank = nullptr;
	class ATank* GetControlledTank() const;
	class ATank* GetPlayerTank() const;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
};
