// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp/DA_PickUp.h"

#include "PaperSpriteComponent.h"
#include "Character/Hero/DA_Hero.h"
#include "Components/BoxComponent.h"

// Sets default values
ADA_PickUp::ADA_PickUp()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(Root);
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	PickUpBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("PickUpBoxComponent"));
	PickUpBoxComponent->SetupAttachment(Root);
	PickUpBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickUpBoxComponent->SetBoxExtent(FVector(15.f,20.f,80.f));
	PickUpBoxComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
}

// Called when the game starts or when spawned
void ADA_PickUp::BeginPlay()
{
	Super::BeginPlay();
	
	PickUpBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADA_PickUp::OnPickUpOverlap);
	
}

void ADA_PickUp::OnPickUpOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADA_Hero* Hero = Cast<ADA_Hero>(OtherActor))
	{
		HandlePickUP(Hero);
	}
	
	
}

void ADA_PickUp::HandlePickUP_Implementation(ADA_Hero* Hero)
{
}




