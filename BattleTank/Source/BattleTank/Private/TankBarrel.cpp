// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Kismet/KismetMathLibrary.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    // Move the Barrel the right amount this frame
	// Given a max elevation speed, and the frame time
    //UE_LOG(LogTemp, Warning, TEXT("Barrel-Elevate() called at speed %f"), RelativeSpeed);
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);
    //UE_LOG(LogTemp, Warning, TEXT("Barrel-Elevate() called at elevation %f"), Elevation);
    SetRelativeRotation(FRotator(Elevation, 0, 0));
}


