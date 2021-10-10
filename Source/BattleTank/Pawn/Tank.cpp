// Created by Pham Hoang Viet in 2021.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraTypes.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Component/TankMotor.h"
#include "Component/TankAiming.h"
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

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->ProjectionMode = ECameraProjectionMode::Perspective;
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	Camera->SetRelativeLocation(FVector(-600.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankAiming = FindComponentByClass<UTankAiming>();
	if (TankAiming)
	{
		TankAiming->Initialize(Turret, Barrel);
	}

	TankMotor = FindComponentByClass<UTankMotor>();
	if (TankMotor)
	{
		TankMotor->SetOwningTank(this);
	}
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
	if (!ensure(TankMotor)) { return; }
	TankMotor->ForwardHandler(AxisValue);
}

void ATank::TurnRight(float AxisValue)
{
	if (!ensure(TankMotor)) { return; }
	TankMotor->TurningHandler(AxisValue);
}

void ATank::Fire()
{
	if (!ensure(TankAiming)) { return; }
	TankAiming->Fire();
}

