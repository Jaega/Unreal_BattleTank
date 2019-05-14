// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#define OUT
void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play"));
    auto PossessedTank = GetControlledTank();
    if(!PossessedTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Play Controller not possessing a tank!"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *PossessedTank->GetName());
    }
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UE_LOG(LogTemp, Warning, TEXT("Ticking!"));
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    // Get World location of linetrace thgrough crosshair
    FVector OutHitLocation; // OUT parameter
    // if it hits landscape
    if(GetSightRayHitLocation(OUT OutHitLocation))
    {
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
    }
        // tell controlled tank to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    HitLocation = FVector(1.0);
    return true;
}


