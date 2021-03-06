// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetThrottle(float Throttle);
	
private:
	TArray<class ASprungWheel*> GetWheels() const;
	UTankTrack();

	void DriveTrack(float CurrentThrottle);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float TrackMaxDrivingForce = 400000; // assume 40 ton tank, 1g acceleration
};
