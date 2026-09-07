// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemies/DA_Enemy_Base.h"

#include "Character/Hero/DA_Hero.h"
#include "Component/DA_HealthComponent.h"
#include "Engine/Engine.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Vfx/DA_VFX_Base.h"

ADA_Enemy_Base::ADA_Enemy_Base()
{
	BaseDamage = 1.f;
	
	EnemyHitStun = 0.8f;
	
	DespawnDelay = 1.f;
}

void ADA_Enemy_Base::WalkTowards(const FVector& Direction)
{
	if (HealthComponent->IsDead() || bIsStunned)
	{
		return;
	}
	AddMovementInput(Direction, 1);
}

void ADA_Enemy_Base::OnHitBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult)
{
	// Horrible this should be like interface and a function this should no be ahndle liek this , 
	ADA_Hero* Hero = Cast<ADA_Hero>(OtherActor);
	if (Hero && OtherComp != Hero->GetHitComponent() && !HealthComponent->IsDead() && !bIsStunned)
	{
		UGameplayStatics::ApplyDamage(OtherActor,BaseDamage,GetController(),this, UDamageType::StaticClass());
	}
}

float ADA_Enemy_Base::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	
	if (!DamageCauser)
	{
		return 0.f;
	}
	
	bIsStunned = true;
	

	const bool bIsDead = HealthComponent->TakeIncomingDamage(DamageAmount);

	if (!bIsDead)
	{
		HitStop();
		
		if (ADA_DungeonCharacter_Base* DamageCauserRef = Cast<ADA_DungeonCharacter_Base>(DamageCauser))
		{
			DamageCauserRef->HitStop();
		}

		FTimerHandle HitTimerHandle;
		FTimerDelegate HitTimerDelegate;
	
		HitTimerDelegate.BindLambda([this]()
		{
			bIsStunned = false;
		});
		
		GetWorld()->GetTimerManager().SetTimer(HitTimerHandle, HitTimerDelegate, EnemyHitStun, false);
	}

	

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ADA_Enemy_Base::OnDeath()
{
	Super::OnDeath();
	
	if (IsValid(DespawnEffect))
	{
		GetWorld()->SpawnActor<ADA_VFX_Base>(DespawnEffect, GetActorLocation(), FRotator::ZeroRotator);
	}
	FTimerHandle DespawnTimerHandle;
	FTimerDelegate DespawnTimerDelegate;
	DespawnTimerDelegate.BindLambda([this]()
	{
		GetWorld()->DestroyActor(this);
	});
	GetWorld()->GetTimerManager().SetTimer(DespawnTimerHandle, DespawnTimerDelegate, DespawnDelay, false);
}

