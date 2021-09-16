// Created by Pham Hoang Viet in 2021.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForcePerTrack = 4000000.0f; // Assume 40 tonne tank, and 1g acceleration 

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
};
