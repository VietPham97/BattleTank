// Created by Pham Hoang Viet in 2021.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	class UStaticMeshComponent* TurretComponent = nullptr;
	class UTankBarrel* BarrelComponent = nullptr;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	
	void AimAt(FVector TargetLocation, float LaunchSpeed);
	void SetTurretComponent(UStaticMeshComponent* TurretComponent);
	void SetBarrelComponent(UTankBarrel* Barrel);

private:
	void RotateBarrelToward(const FVector& AimDirection);
};
