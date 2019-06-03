// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
}
void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    //UE_LOG(LogTemp, Warning, TEXT("%s on hit"), *GetName())
    DriveTrack();
    ApplySideWaysForce();
    CurrentThrottle = 0; // Reset throttle
}

void UTankTrack::ApplySideWaysForce()
{
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); 
    auto CorrectAcceleration = - SlippageSpeed / DeltaTime * GetRightVector(); // Calc required acceleration to correct
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());  // Calc and Apply sideways force
    auto CorrectionForce = (TankRoot->GetMass() * CorrectAcceleration) / 2;
    TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, +1);
    //CurrentThrottle = Throttle;
}

void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

    UE_LOG(LogTemp, Warning, TEXT("%f: %s add force"), GetWorld()->GetTimeSeconds(), *GetName())
}


