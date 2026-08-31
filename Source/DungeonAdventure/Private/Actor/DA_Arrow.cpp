// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DA_Arrow.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ADA_Arrow::ADA_Arrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void ADA_Arrow::BeginPlay()
{
	Super::BeginPlay();
	
}


