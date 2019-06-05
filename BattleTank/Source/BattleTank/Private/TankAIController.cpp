// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

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

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if(InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if( !ensure(PossessedTank)) { return; }
        // Subscribe listener
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}

void ATankAIController::OnPossessedTankDeath()
{
    //UE_LOG(LogTemp, Warning, TEXT("Received!"))
    GetPawn()->DetachFromControllerPendingDestroy();
}



