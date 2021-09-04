// Created by Pham Hoang Viet in 2021.


#include "TankAIController.h"
#include "Pawn/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	this->Tank = GetControlledTank();
	this->PlayerTank = GetPlayerTank();
	if (!this->PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController could not find PlayerTank"));
	}
	else
	{
		FString TankName = this->PlayerTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *TankName);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!this->Tank) { return; }
	if (!this->PlayerTank) { return; }

	// Chase the player

	// Aim toward player
	FVector PlayerLocation = this->PlayerTank->GetActorLocation();
	this->Tank->AimAt(PlayerLocation);

	// Fire if ready
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
