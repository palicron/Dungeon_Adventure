// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Character/DA_DungeonCharacter_Base.h"
#include "DA_Hero.generated.h"

class UBoxComponent;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class DUNGEONADVENTURE_API ADA_Hero : public ADA_DungeonCharacter_Base
{
	GENERATED_BODY()
	
	ADA_Hero();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable)
	FVector2D GetMoveAxis() const { return MoveAxis; };
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	TObjectPtr<UBoxComponent> HitComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	FVector2D MoveAxis;
	
	UFUNCTION()
	void Move(const FInputActionValue& InputActionValue);
	
	
};
