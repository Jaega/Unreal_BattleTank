// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
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
    if(GetSightRayHitLocation(OutHitLocation))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
    }
        // tell controlled tank to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // Find crosshair position (in pixel coordinates)
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
    //UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());
    // De-project the screen position of the crosshair to a world direction
    FVector LookDirection; 
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());
    }
    // Line-tracing along that direction, see what we hit (up to max range)
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // To be discarded
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

