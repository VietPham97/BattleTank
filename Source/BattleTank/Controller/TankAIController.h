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

protected:
	virtual void BeginPlay() override;

public:
	class ATank* GetControlledTank() const;
	
};
