// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();  // Get Player's pawn
    auto ControlledPawn = GetPawn(); // Get AI's pawn
    if(!ensure(PlayerPawn)) { return; }

    // Move towards the player
    MoveToActor(PlayerPawn, AcceptanceRadius);
    // Aim at the player
    auto AimingComponent = ControlledPawn->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)) { return; }
    AimingComponent->AimAt(PlayerPawn->GetActorLocation()); 
    // fire if ready
    if(AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire();
    }
}




