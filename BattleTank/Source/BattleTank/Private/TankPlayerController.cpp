// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();    
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(ensure(AimingComponent))
    {
        FoundAimingComponent(AimingComponent);
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Aiming Component not found."));
    }
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetPawn()){ return; }
    
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)) { return; }
    // Get World location of linetrace thgrough crosshair
    FVector OutHitLocation; // OUT parameter
    // if it hits landscape
    if(GetSightRayHitLocation(OutHitLocation))
    {
       AimingComponent->AimAt(OutHitLocation); // tell controlled tank to aim at this point
    }
        
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // Find crosshair position (in pixel coordinates)
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
    // De-project the screen position of the crosshair to a world direction
    FVector LookDirection; 
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        if(GetLookVectorHitLocation(LookDirection, OutHitLocation))
        {
            // Line-tracing along that direction, see what we hit (up to max range)
            return true;
        }
    }
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // To be discarded
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
    FHitResult OutHitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + LookDirection * LineTraceRange;
    
   if(GetWorld()->LineTraceSingleByChannel(
        OutHitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility)
        )
   {
       OutHitLocation = OutHitResult.Location;
       return true;
   }
   return false;
}
