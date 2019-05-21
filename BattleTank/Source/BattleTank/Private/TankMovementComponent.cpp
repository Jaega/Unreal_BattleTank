// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}
void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
    //auto TankName = GetOwner()->GetName();
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    IntendMoveForward(ForwardThrow);
    //auto MoveVelocityString = MoveVelocity.ToString();
    //UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if(! LeftTrack || ! RightTrack) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
    // TODO prevent double-speed due to dual control
}

void UTankMovementComponent::IntendMoveBackward(float Throw)
{
    if(! LeftTrack || ! RightTrack) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
    // TODO prevent double-speed due to dual control
}



void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if(! LeftTrack || ! RightTrack) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
    // TODO prevent double-speed due to dual control
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
    if(! LeftTrack || ! RightTrack) { return; }
    LeftTrack->SetThrottle(-Throw);
    RightTrack->SetThrottle(Throw);
    // TODO prevent double-speed due to dual control
}

