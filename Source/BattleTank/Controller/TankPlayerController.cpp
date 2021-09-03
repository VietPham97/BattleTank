// Created by Pham Hoang Viet in 2021.


#include "TankPlayerController.h"
#include "Pawn/Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (!Tank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing any Tank"));
	}
	else
	{
		FString TankName = Tank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *TankName);
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
