// Created by Pham Hoang Viet in 2021.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraTypes.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Component/TankMotor.h"
#include "Component/TankAimingComponent.h"
#include "Component/TankTrack.h"
#include "Component/TankTurret.h"
#include "Component/TankBarrel.h"
#include "Actor/Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	SetRootComponent(Body);

	TankDirection = CreateDefaultSubobject<UArrowComponent>(FName("Arrow"));
	TankDirection->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);

	LeftTrack = CreateDefaultSubobject<UTankTrack>(FName("Left Track"));
	LeftTrack->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform, "Left Track");

	RightTrack = CreateDefaultSubobject<UTankTrack>(FName("Right Track"));
	RightTrack->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform, "Right Track");

	Turret = CreateDefaultSubobject<UTankTurret>(FName("Turret"));
	Turret->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform, "Turret");

	Barrel = CreateDefaultSubobject<UTankBarrel>(FName("Barrel"));
	Barrel->AttachToComponent(Turret, FAttachmentTransformRules::KeepRelativeTransform, "Barrel");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritRoll = false;
	SpringArm->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	SpringArm->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->ProjectionMode = ECameraProjectionMode::Perspective;
	CameraComponent->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	CameraComponent->SetRelativeLocation(FVector(-600.0f, 0.0f, 0.0f));

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	Motor = CreateDefaultSubobject<UTankMotor>(FName("Motor"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent->SetTurretComponent(Turret);
	AimingComponent->SetBarrelComponent(Barrel);

	Motor->SetLeftTrackComponent(LeftTrack);
	Motor->SetRightTrackComponent(RightTrack);
}

void ATank::AimAt(FVector HitLocation)
{
	AimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis(FName("TurnRight"), this, &ATank::TurnRight); 
	PlayerInputComponent->BindAction(FName("Fire"), EInputEvent::IE_Pressed, this, &ATank::Fire);
}

void ATank::MoveForward(float AxisValue)
{
	Motor->ForwardHandler(AxisValue);
}

void ATank::TurnRight(float AxisValue)
{
	Motor->TurningHandler(AxisValue);
}

void ATank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!bIsReloaded) {
		return;
	}

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileObject, 
		Barrel->GetSocketLocation("Projectile"),
		Barrel->GetSocketRotation("Projectile")
	);

	Projectile->LaunchWithSpeed(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}

