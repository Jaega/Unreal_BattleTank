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
    // Get Player's tank
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    // Get AI's tank
    auto ControlledTank = Cast<ATank>(GetPawn());
    if(PlayerTank) {
        // Move towards the player
        MoveToActor(PlayerTank, AcceptanceRadius);
        // Aim at the player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());
        // fire if ready
        ControlledTank->Fire();
    }
}




