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
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// First fire should happen after first loading
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if(GetRoundsLeft() <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if(isBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::isBarrelMoving()
{
	if(!ensure(Barrel)) { return false; }
	auto BarrelForwardVector = Barrel->GetForwardVector();
	return !BarrelForwardVector.Equals(AimDirection, 0.01); // 0.01 is tolerance
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		
	} 
	else 
	{
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
	
	// always yaw in the shortest route
	if(FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	//Turret->Rotate(FMath::Abs(DeltaRotator.Yaw));
	 
}

void UTankAimingComponent::Fire()
{
	if(FiringState == EFiringState::Aiming || FiringState == EFiringState::Locked ) 
	{
		// Spawn a projectile at the socket location of the barrel
		if(!ensure(Barrel)) { return; }
		if(!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

