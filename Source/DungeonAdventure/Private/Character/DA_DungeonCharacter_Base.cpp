// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DA_DungeonCharacter_Base.h"

#include "PaperFlipbookComponent.h"
#include "Component/DA_HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ADA_DungeonCharacter_Base::ADA_DungeonCharacter_Base()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0,1080,0);
	GetSprite()->SetAbsolute(false,true,false);
	bUseControllerRotationYaw = false;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	
	HitBoxComponent = CreateDefaultSubobject<UBoxComponent>("Hit Box Component");
	HitBoxComponent->SetupAttachment(RootComponent);
	HitBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBoxComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Overlap);
	
	HealthComponent = CreateDefaultSubobject<UDA_HealthComponent>("Health Component");
	
}

void ADA_DungeonCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
	HitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADA_DungeonCharacter_Base::OnHitBoxOverlap);
}

void ADA_DungeonCharacter_Base::OnHitBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                const FHitResult& SweepResult)
{
}
