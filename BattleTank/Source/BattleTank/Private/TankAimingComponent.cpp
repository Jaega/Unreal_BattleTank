// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

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
	//auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);

	if(!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool hasValidProjectileSoln = UGameplayStatics::SuggestProjectileVelocity
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

	if (hasValidProjectileSoln)
	{
		// Calculate the OutLaunchVelocity
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Firing at %s"), *AimDirection.ToString());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No available valid solution"));
	}
	
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}