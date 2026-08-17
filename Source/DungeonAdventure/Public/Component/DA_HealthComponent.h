// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DA_HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONADVENTURE_API UDA_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UDA_HealthComponent();

	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return CurrentHealth; }
	
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const { return MaxHealth; }
	
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return bDead; }
	
	virtual void BeginPlay() override;
	
	UFUNCTION( BlueprintCallable)
	virtual bool TakeIncomingDamage(const float DamageAmount);
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	
	UPROPERTY(BlueprintReadWrite, Category = "Health")
	float CurrentHealth;
	
	UPROPERTY(BlueprintReadWrite, Category = "Health")
	uint8 bDead : 1;
	




		
};
