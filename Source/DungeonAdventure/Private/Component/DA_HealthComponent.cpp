// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DA_HealthComponent.h"

// Sets default values for this component's properties
UDA_HealthComponent::UDA_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	CurrentHealth = 100.f;
	bDead = false;
	
	bInvincible = false;
	
	InvincibilityTimer = 1.f;
}


// Called when the game starts
void UDA_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}

bool UDA_HealthComponent::TakeIncomingDamage(const float DamageAmount)
{
	
	if (bInvincible)
	{
		return false;
	}
	
	if (bDead)
	{
		return true;
	}
	
	OnDamageTakeDelegate.Broadcast(DamageAmount);
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
	
	if (FMath::IsNearlyZero(CurrentHealth))
	{
		bDead = true;
		return true;
	}
	

	
	//TODO HORRENDO this shoudl be next frame 
	GetWorld()->GetTimerManager().SetTimer(DelayInvincibilityTimerHandle, this, &UDA_HealthComponent::ActivateInvincible, 0.1f);
	GetWorld()->GetTimerManager().SetTimer(InvincibilityTimerHandle, this, &UDA_HealthComponent::DeactivateInvincible, InvincibilityTimer);
	return false;
}

void UDA_HealthComponent::Health(const float HealthAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + HealthAmount, 0.f, MaxHealth);
	OnHealthChangedDelegate.Broadcast(CurrentHealth);
}

void UDA_HealthComponent::ActivateInvincible()
{
	bInvincible = true; 
	OnInvincibilityStartedDelegate.Broadcast();
}

void UDA_HealthComponent::DeactivateInvincible()
{
	bInvincible = false;
	OnInvincibilityEndDelegate.Broadcast();
}


