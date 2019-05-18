// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if(GetPlayerTank())
    {
        // TODO move towards the player
        // Aim at the player
        //GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
        // fire if ready
    }
}
ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(!PlayerPawn) {return nullptr;}
    return Cast<ATank>(PlayerPawn);
}


