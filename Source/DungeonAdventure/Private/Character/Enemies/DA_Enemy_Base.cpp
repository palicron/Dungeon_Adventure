// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemies/DA_Enemy_Base.h"

#include "Character/Hero/DA_Hero.h"
#include "Component/DA_HealthComponent.h"
#include "Engine/Engine.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

ADA_Enemy_Base::ADA_Enemy_Base()
{
	BaseDamage = 10.f;
}

void ADA_Enemy_Base::WalkTowards(const FVector& Direction)
{
	if (HealthComponent->IsDead())
	{
		return;
	}
	AddMovementInput(Direction, 1);
}

void ADA_Enemy_Base::OnHitBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult)
{
	// Horrible this should be like interface and a function this should no be ahndle liek this , 
	ADA_Hero* Hero = Cast<ADA_Hero>(OtherActor);
	if (Hero && OtherComp != Hero->GetHitComponent())
	{
		UGameplayStatics::ApplyDamage(OtherActor,10.f,GetController(),this, UDamageType::StaticClass());
	}
}

float ADA_Enemy_Base::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	
	if (!DamageCauser)
	{
		return 0.f;
	}
	
	const bool bIsDead = HealthComponent->TakeIncomingDamage(DamageAmount);
	
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %f"), HealthComponent->GetHealth()));

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
