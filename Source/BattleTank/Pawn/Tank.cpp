// Created by Pham Hoang Viet in 2021.


#include "Tank.h"
#include "Component/TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>("AimingComponent");
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	this->AimingComponent->AimAt(HitLocation, this->LaunchSpeed);
}

void ATank::SetBarrelComponent(UTankBarrel* Barrel)
{
	this->AimingComponent->SetBarrelComponent(Barrel);
}

