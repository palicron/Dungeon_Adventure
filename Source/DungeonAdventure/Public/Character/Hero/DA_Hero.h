// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Character/DA_DungeonCharacter_Base.h"
#include "DA_Hero.generated.h"

class ADA_Arrow;
class UDA_MainHUD;
class UPaperZDAnimSequence;
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
public:
	
	ADA_Hero();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	FVector2D GetMoveAxis() const { return MoveAxis; };
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(blueprintPure)
	bool CanTakeAction() const;
	
	UFUNCTION(BlueprintCallable)
	virtual void CheckDamageHitComponent();
	
	UFUNCTION(BlueprintCallable)
	UBoxComponent* GetHitComponent() const { return HitComponent; }
protected:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="HUD")
	TSubclassOf<UDA_MainHUD> MainHUDClass;
	
	UPROPERTY()
	TObjectPtr<UDA_MainHUD> MainHUD;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	TObjectPtr<UBoxComponent> HitComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input")
	TObjectPtr<UInputAction> FireAction;
    	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Animation")
	TObjectPtr<UPaperZDAnimSequence> HitSequence;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Animation")
	TObjectPtr<UPaperZDAnimSequence> AttackSequence;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Animation")
	TObjectPtr<UPaperZDAnimSequence> FireSequence;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Fire")
	TSubclassOf<ADA_Arrow> ArrowClass;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Fire")
	float ArrowPositionOffset;
	
	FTimerHandle FlickerTimerHandle;
	
	FVector2D MoveAxis;
	
	uint8 bAttacking : 1;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Animation|Flickerin")
	float InvincibilityTimer;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Animation|Flickerin")
	float InvincibilityTickRate;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Animation")
	float AttackPlayRate;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Animation")
	float FirePlayRate;
	
	float InvincibilityTimerRemaining;
	
	UFUNCTION()
	void Move(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void Attack();
	
	UFUNCTION()
	void Fire();
	
	virtual void OnDamageTaken(float DamageTaken) override;
	
	virtual void EndKnockBack() override;
	
	UFUNCTION()
	void OnInvincibilityTimerStarted();
	
	UFUNCTION()
	void OnInvincibilityTimerExpired();
	
	UFUNCTION(BlueprintCallable)
	void SpawnArrow();
	


};
