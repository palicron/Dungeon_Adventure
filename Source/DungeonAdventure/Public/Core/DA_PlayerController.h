// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DA_PlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class DUNGEONADVENTURE_API ADA_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;
	
protected:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DungeonInputContext;
	
	
};
