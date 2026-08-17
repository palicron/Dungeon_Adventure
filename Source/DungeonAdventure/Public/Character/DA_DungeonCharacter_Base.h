// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "DA_DungeonCharacter_Base.generated.h"

class UDA_HealthComponent;
class UBoxComponent;
/**
 * 
 */
UCLASS(Abstract,Blueprintable)
class DUNGEONADVENTURE_API ADA_DungeonCharacter_Base : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	
	ADA_DungeonCharacter_Base();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	TObjectPtr<UBoxComponent> HitBoxComponent;
	
	virtual void BeginPlay() override;
	
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	TObjectPtr<UDA_HealthComponent> HealthComponent;
	
	UFUNCTION(BlueprintCallable)
	virtual void OnHitBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	

};
