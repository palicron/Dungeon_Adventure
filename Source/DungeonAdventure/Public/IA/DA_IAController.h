// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DA_IAController.generated.h"

class ADA_Enemy_Base;
class ADA_Hero;
/**
 * 
 */
UCLASS()
class DUNGEONADVENTURE_API ADA_IAController : public AAIController
{
	GENERATED_BODY()
	
public:
	
	ADA_IAController();
	
	
	
protected:
	
	TWeakObjectPtr<ADA_Hero> Player;
	TWeakObjectPtr<ADA_Enemy_Base> PossesPawn;
	
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void Tick(float DeltaSeconds) override;
};
