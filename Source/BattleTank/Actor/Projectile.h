// Created by Pham Hoang Viet in 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
\
class UArrowComponent;
class UProjectileMovementComponent;

UCLASS(meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

private:
	// Helpful debug tool - which way is the projectile fowarding?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ProjectileDirection = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* MovementComponent = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchWithSpeed(float Speed);

};
