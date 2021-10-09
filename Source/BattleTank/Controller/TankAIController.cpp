// Created by Pham Hoang Viet in 2021.


#include "TankAIController.h"
#include "Component/TankAiming.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LocatePlayerTank();
}

void ATankAIController::LocatePlayerTank()
{
	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(ControlledTank && PlayerTank)) { return; }
	
	// Chase the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO: Check radius is in cm

	auto TankAiming = ControlledTank->FindComponentByClass<UTankAiming>();
	auto PlayerLocation = PlayerTank->GetActorLocation();
	TankAiming->AimAt(PlayerLocation);
	TankAiming->Fire(); // TODO: Limit firing rate
}

