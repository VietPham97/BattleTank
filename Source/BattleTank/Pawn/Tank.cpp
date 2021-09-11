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

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent) 
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Tank"));
	}

	TankDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	TankDirection->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TankBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	TankBody->SetSimulatePhysics(true);
	TankBody->SetMassOverrideInKg(TEXT("Mass In Kg"), 40000.0f);
	TankBody->AttachToComponent(TankDirection, FAttachmentTransformRules::KeepRelativeTransform);

	TankTrackLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrackLeft"));
	TankTrackLeft->AttachToComponent(TankBody, FAttachmentTransformRules::KeepRelativeTransform, "Left Track");

	TankTrackRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrackRight"));
	TankTrackRight->AttachToComponent(TankBody, FAttachmentTransformRules::KeepRelativeTransform, "Right Track");

	TankTurret = CreateDefaultSubobject<UTankTurret>(TEXT("Turret"));
	TankTurret->AttachToComponent(TankBody, FAttachmentTransformRules::KeepRelativeTransform, "Turret");

	TankBarrel = CreateDefaultSubobject<UTankBarrel>(TEXT("Barrel"));
	TankBarrel->AttachToComponent(TankTurret, FAttachmentTransformRules::KeepRelativeTransform, "Barrel");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritRoll = false;
	SpringArm->AttachToComponent(TankBody, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	SpringArm->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->ProjectionMode = ECameraProjectionMode::Perspective;
	CameraComponent->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	CameraComponent->SetRelativeLocation(FVector(-600.0f, 0.0f, 0.0f));

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>("AimingComponent");
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent->SetTurretComponent(TankTurret);
	AimingComponent->SetBarrelComponent(TankBarrel);
}

void ATank::AimAt(FVector HitLocation)
{
	this->AimingComponent->AimAt(HitLocation, this->LaunchSpeed);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
}

