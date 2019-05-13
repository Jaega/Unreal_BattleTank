// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto PossessedTank = GetControlledTank();
    if(!PossessedTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller not possessing a tank!"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *PossessedTank->GetName());
    }
    UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play"));
    GetControlledTank();
}
ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


