// Created by Pham Hoang Viet in 2021.


#include "TankAIController.h"
#include "Pawn/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController could not find PlayerTank"));
	}
	else
	{
		FString TankName = PlayerTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *TankName);
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}
