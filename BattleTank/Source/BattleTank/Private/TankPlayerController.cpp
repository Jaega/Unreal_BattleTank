// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto PossessedTank = GetControlledTank();
    if(!PossessedTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Play Controller not possessing a tank!"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *PossessedTank->GetName());
    }
    UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play"));
    GetControlledTank();
}
ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


