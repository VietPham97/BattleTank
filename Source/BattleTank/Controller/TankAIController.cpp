// Created by Pham Hoang Viet in 2021.


#include "TankAIController.h"
#include "Pawn/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	this->Tank = Cast<ATank>(GetPawn());
	this->PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Tank) { return; }
	if (!PlayerTank) { return; }

	// Chase the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO: Check radius is in cm

	Tank->AimAt(PlayerTank->GetActorLocation());
	//Tank->Fire(); // TODO: Limit firing rate
}

