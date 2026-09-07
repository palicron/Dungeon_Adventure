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
	
	HitStopTime = 0.15f;
	
	bIsStunned = false;
	
	InvincibilityTimer = 1;
	
	InvincibilityTickRate = 0.1f;
}

void ADA_DungeonCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	SpriteColor = GetSprite()->GetSpriteColor();
	
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
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, 
			FString::Printf(TEXT("World delta for current frame equals %hs"), HealthComponent->GetInvincible()? "True" : "False"));
	GetSprite()->SetSpriteColor(SpriteColor);


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
			GetSprite()->SetSpriteColor(SpriteColor);
			EndKnockBack();
			return;
		}
		
		KnockBackTimerRemaining -= KnockBackPlayRate;
	});
	
	GetWorld()->GetTimerManager().SetTimer(KnockBackTimerHandle, KnockBackDelegate, KnockBackPlayRate, true);
}

void ADA_DungeonCharacter_Base::EndKnockBack()
{
}

void ADA_DungeonCharacter_Base::HitStop()
{
	CustomTimeDilation = 0.f;
	FTimerHandle HitStopTimerHandle;
	FTimerDelegate HitStopDelegate;
	HitStopDelegate.BindWeakLambda(this, [this]()
	{
		CustomTimeDilation = 1.f;
	});
	GetWorld()->GetTimerManager().SetTimer(HitStopTimerHandle, HitStopDelegate, HitStopTime, false);
}

void ADA_DungeonCharacter_Base::FlashSprite()
{
	//TODO: probalby i need to add some function to customise the duration for the moment Knockback is cleaning this
	GetSprite()->SetSpriteColor(FLinearColor::Red);

	
}

float ADA_DungeonCharacter_Base::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (!HealthComponent->IsDead() &&  !HealthComponent->GetInvincible())
	{
		KnockBack((GetActorLocation() - DamageCauser->GetActorLocation()).GetSafeNormal());
		FlashSprite();
	}
	else if (HealthComponent->IsDead())
	{
		OnDeath();
	}
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ADA_DungeonCharacter_Base::SetSpriteVisibility(const bool bIsVisible)
{
	
	GetSprite()->SetVisibility(bIsVisible);
}

void ADA_DungeonCharacter_Base::OnDeath()
{
	bIsStunned = false;
	HitBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
