// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play"));
    GetControlledTank();
}
ATank* ATankPlayerController::GetControlledTank() const
{
    ATank* MyTank = Cast<ATank>(GetPawn());
    UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *MyTank->GetName());
    return MyTank;
}


