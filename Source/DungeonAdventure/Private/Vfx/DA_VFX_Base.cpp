// Fill out your copyright notice in the Description page of Project Settings.


#include "Vfx/DA_VFX_Base.h"

#include "PaperFlipbookComponent.h"

// Sets default values
ADA_VFX_Base::ADA_VFX_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
	PaperFlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ADA_VFX_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADA_VFX_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

