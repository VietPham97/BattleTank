// Created by Pham Hoang Viet in 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Helpful debug tool - which way is the tank facing?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* TankDirection = nullptr;

	// Static Mesh for the tank body
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Body = nullptr;

	// Static Mesh for the tank track left
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	class UTankTrack* LeftTrack = nullptr;

	// Static Mesh for the tank track right
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	class UTankTrack* RightTrack = nullptr;

	// Static Mesh for the tank turret
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	class UTankTurret* Turret = nullptr;

	// Static Mesh for the tank barrel
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	class UTankBarrel* Barrel = nullptr;

	// Spring-Arm for the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm = nullptr;

	// Third-person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera = nullptr;

	class UTankAiming* TankAiming = nullptr;
	class UTankMotor* TankMotor = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float AxisValue);
	void TurnRight(float AxisValue);

	void LookUp(float AxisValue);
	void LookRight(float AxisValue);

	void Fire();
};
