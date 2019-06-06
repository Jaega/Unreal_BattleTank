// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));

	SetRootComponent(Mass);
	Wheel->SetupAttachment(Mass);
	Spring->SetupAttachment(Mass);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

