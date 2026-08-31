// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DA_Arrow.generated.h"

class UProjectileMovementComponent;

UCLASS()
class DUNGEONADVENTURE_API ADA_Arrow : public AActor
{
	GENERATED_BODY()
	
public:	

	ADA_Arrow();

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	virtual void BeginPlay() override;
	

};
