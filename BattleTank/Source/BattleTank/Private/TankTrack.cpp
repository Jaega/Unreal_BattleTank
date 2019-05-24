// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // Calc the slippage speed
    // Calc required acceleration to correct
    auto CorrectAcceleration = - SlippageSpeed / DeltaTime * GetRightVector();
    // Calc and Apply sideways force
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner() -> GetRootComponent());
    auto CorrectionForce = TankRoot->GetMass() * CorrectAcceleration / 2;
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast< UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


