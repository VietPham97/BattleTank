// Created by Pham Hoang Viet in 2021.


#include "TankAIController.h"
#include "Component/TankAiming.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	ControlledTank = GetPawn();
	TankAiming = ControlledTank->FindComponentByClass<UTankAiming>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LocatePlayerTank();
}

void ATankAIController::LocatePlayerTank()
{
	if (!ensure(ControlledTank && PlayerTank)) { return; }
	
	// Chase the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO: Check radius is in cm

	auto PlayerLocation = PlayerTank->GetActorLocation();
	TankAiming->AimAt(PlayerLocation);

	auto FiringState = TankAiming->GetFiringState();
	if (FiringState == EFiringState::Locked)
	{
		TankAiming->Fire(); // TODO: Limit firing rate
	}
}

