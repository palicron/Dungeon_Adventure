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
	
	KnockBackTimer = 0.2f;
	
	bKnockBack = false;
	
	KnockBackStrength = 800.f;
	
	KnockBackTimerRemaining = 0.f;
	
	KnockBackPlayRate = 0.02f;
}

void ADA_DungeonCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
	HitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADA_DungeonCharacter_Base::OnHitBoxOverlap);
	HealthComponent->OnDamageTakeDelegate.AddUniqueDynamic(this, &ADA_DungeonCharacter_Base::OnDamageTaken);
}

void ADA_DungeonCharacter_Base::OnHitBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                const FHitResult& SweepResult)
{
}

void ADA_DungeonCharacter_Base::OnDamageTaken(float DamageTaken)
{
}

void ADA_DungeonCharacter_Base::KnockBack(const FVector& Direction)
{
	KnockBackTimerRemaining = KnockBackTimer;
	FTimerDelegate KnockBackDelegate;
	KnockBackDelegate.BindWeakLambda(this, [this,Direction]()
	{
		float GetTargetForce = KnockBackStrength / 0.016 ; 
		GetMovementComponent()->Velocity = Direction * (GetTargetForce * GetWorld()->GetDeltaSeconds());
		
		if (KnockBackTimerRemaining <= 0.f)
		{
			GetWorld()->GetTimerManager().ClearTimer(KnockBackTimerHandle);
			KnockBackTimerHandle.Invalidate();
			return;
		}
		
		KnockBackTimerRemaining -= KnockBackPlayRate;
	});
	
	GetWorld()->GetTimerManager().SetTimer(KnockBackTimerHandle, KnockBackDelegate, KnockBackPlayRate, true);
}

float ADA_DungeonCharacter_Base::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (!HealthComponent->IsDead())
	{
		KnockBack((GetActorLocation() - DamageCauser->GetActorLocation()).GetSafeNormal());
	}
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
