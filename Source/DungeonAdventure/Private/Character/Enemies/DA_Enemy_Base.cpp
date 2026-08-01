// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemies/DA_Enemy_Base.h"

#include "Character/Hero/DA_Hero.h"
#include "Engine/Engine.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

void ADA_Enemy_Base::WalkTowards(const FVector& Direction)
{
	AddMovementInput(Direction, 1);
}

void ADA_Enemy_Base::OnHitBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ADA_Hero>())
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
	
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %ls"), *DamageCauser->GetName()));

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
