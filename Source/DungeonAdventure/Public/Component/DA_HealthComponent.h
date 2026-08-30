// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DA_HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTakeSignature, float, RemainingHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInvincibilityStartedSiganature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInvincibilityEndSiganature);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONADVENTURE_API UDA_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UDA_HealthComponent();
	
		
	UPROPERTY(BlueprintAssignable)
	FOnDamageTakeSignature OnDamageTakeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnInvincibilityStartedSiganature OnInvincibilityStartedDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnInvincibilityEndSiganature OnInvincibilityEndDelegate;
	
	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return CurrentHealth; }
	
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const { return MaxHealth; }
	
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return bDead; }
	
	virtual void BeginPlay() override;
	
	UFUNCTION( BlueprintCallable)
	virtual bool TakeIncomingDamage(const float DamageAmount);
	
	bool GetInvincible() const { return bInvincible; }
	
protected:
	
	FTimerHandle DelayInvincibilityTimerHandle;
	FTimerHandle InvincibilityTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	
	UPROPERTY(BlueprintReadWrite, Category = "Health")
	float CurrentHealth;
	
	UPROPERTY(BlueprintReadWrite, Category = "Health")
	uint8 bDead : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float InvincibilityTimer;
	
	uint8 bInvincible : 1;
	
	
	
	void ActivateInvincible();
	void DeactivateInvincible();




		
};
