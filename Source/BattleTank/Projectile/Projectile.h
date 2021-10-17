// Created by Pham Hoang Viet in 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UArrowComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;
class URadialForceComponent;

UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

private:
	// Helpful debug tool - which way is the projectile fowarding?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ProjectileDirection = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Explosion", meta = (AllowPrivateAccess = "true"))
	URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectileMovement", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	float DestroyDelay = 3.0f;

public:	
	// Sets default values for this actor's properties
	AProjectile();

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpired();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void LaunchWithSpeed(float Speed);

};
