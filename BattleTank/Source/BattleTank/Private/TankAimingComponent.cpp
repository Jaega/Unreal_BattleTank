// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if(!ensure(BarrelToSet)) { return; }
	Barrel = BarrelToSet;

	if(!ensure(TurretToSet)) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{	
	if(!ensure(Barrel)) { return; }

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


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if(!ensure(Barrel && Turret)) { return; }
	// Calculate difference between current rotation and given AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->Rotate(DeltaRotator.Yaw); // TODO remove magic number
}

void UTankAimingComponent::Fire()
{
	if(!ensure(Barrel && ProjectileBlueprint)) { return; }
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if(bIsReloaded) {
		// Spawn a projectile at the socket location of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		Projectile->LaunchProjectile(LaunchSpeed);
		// reset last fire time after firing
		LastFireTime = FPlatformTime::Seconds();
	}
	
}