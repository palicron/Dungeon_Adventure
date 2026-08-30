// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DA_MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONADVENTURE_API UDA_MainHUD : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void InitHealthBar(const float MaxHealth);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthBar(const float CurrentHealth, const float MaxHealth);
	
};
