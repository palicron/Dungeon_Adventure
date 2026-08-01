// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DA_DungeonCharacter_Base.h"
#include "DA_Enemy_Base.generated.h"

/**
 * 
 */
UCLASS(Abstract,Blueprintable)
class DUNGEONADVENTURE_API ADA_Enemy_Base : public ADA_DungeonCharacter_Base
{
	GENERATED_BODY()
	
	
public:
	
	UFUNCTION(BlueprintCallable)
	void WalkTowards(const FVector& Direction);
	
	
	virtual void OnHitBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
