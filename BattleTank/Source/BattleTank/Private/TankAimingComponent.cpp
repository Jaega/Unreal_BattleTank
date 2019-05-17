// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{	
	if(!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveValidProjectileSoln = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity, // OUT parameter -> launch direction
		StartLocation,
		HitLocation, // desired end location
		LaunchSpeed,
		false, // high arc or not
		0, // CollisionRadius (Radius of the projectile)
		0, // OverrideGravityZ (0 means "do not override")
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveValidProjectileSoln)
	{
		// Calculate the OutLaunchVelocity
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No available valid solution"));
	}
	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Calculate difference between current rotation and given AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	
	Barrel->Elevate(5); // TODO remove magic number
}