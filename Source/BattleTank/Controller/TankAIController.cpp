// Created by Pham Hoang Viet in 2021.


#include "TankAIController.h"
#include "Pawn/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (!Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing any Tank"));
	}
	else
	{
		FString TankName = Tank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *TankName);
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
