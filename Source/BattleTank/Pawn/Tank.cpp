// Created by Pham Hoang Viet in 2021.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraTypes.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Component/TankAimingComponent.h"
#include "Component/TankTurret.h"
#include "Component/TankBarrel.h"
#include "Actor/Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent) 
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Tank"));
	}

	TankDirection = CreateDefaultSubobject<UArrowComponent>(FName("Direction"));
	TankDirection->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	Body->SetSimulatePhysics(true);
	Body->SetMassOverrideInKg(TEXT("Mass In Kg"), 40000.0f);
	Body->AttachToComponent(TankDirection, FAttachmentTransformRules::KeepRelativeTransform);

	TrackLeft = CreateDefaultSubobject<UStaticMeshComponent>(FName("TrackLeft"));
	TrackLeft->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform, "Left Track");

	TrackRight = CreateDefaultSubobject<UStaticMeshComponent>(FName("TrackRight"));
	TrackRight->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform, "Right Track");

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
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent->SetTurretComponent(Turret);
	AimingComponent->SetBarrelComponent(Barrel);
}

void ATank::AimAt(FVector HitLocation)
{
	AimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!Barrel) {
		return;
	}

	// Spawn the projectile
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileObject, 
		Barrel->GetSocketLocation("Projectile"),
		Barrel->GetSocketRotation("Projectile")
	);

	// Launch the projectile
	Projectile->LaunchWithSpeed(LaunchSpeed);
}

