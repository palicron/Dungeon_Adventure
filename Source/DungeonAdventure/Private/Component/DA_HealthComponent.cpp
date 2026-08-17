// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DA_HealthComponent.h"

// Sets default values for this component's properties
UDA_HealthComponent::UDA_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	CurrentHealth = 100.f;
	bDead = false;
}


// Called when the game starts
void UDA_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	
}

bool UDA_HealthComponent::TakeIncomingDamage(const float DamageAmount)
{
	if (bDead)
	{
		return true;
	}
	
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);

	if (FMath::IsNearlyZero(CurrentHealth))
	{
		bDead = true;
		return true;
	}
	return false;
}


