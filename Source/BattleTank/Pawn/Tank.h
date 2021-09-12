// Created by Pham Hoang Viet in 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;
class UTankAimingComponent;
class UStaticMeshComponent;
class UTankTurret;
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Helpful debug tool - which way is the tank facing?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* TankDirection = nullptr;

	// Static Mesh for the tank body
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Body = nullptr;

	// Static Mesh for the tank track left
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TrackLeft = nullptr;

	// Static Mesh for the tank track right
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TrackRight = nullptr;

	// Static Mesh for the tank turret
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UTankTurret* Turret = nullptr;

	// Static Mesh for the tank barrel
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UTankBarrel* Barrel = nullptr;

	// Spring-Arm for the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm = nullptr;

	// Third-person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankAiming", meta = (AllowPrivateAccess = "true"))
	UTankAimingComponent* AimingComponent = nullptr;

	// Projectile
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileObject;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000; // 40 m/s ~ 4,000 cm/s

	float ReloadTimeInSeconds = 3.0f;
	double LastFireTime = 0;

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
};
