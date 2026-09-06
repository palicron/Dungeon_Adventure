// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DA_PickUp.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;
class ADA_Hero;
UCLASS()
class DUNGEONADVENTURE_API ADA_PickUp : public AActor
{
	GENERATED_BODY()
	
public:	

	ADA_PickUp();

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Components")
	TObjectPtr<UPaperSpriteComponent> SpriteComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Components")
	TObjectPtr<UBoxComponent> PickUpBoxComponent;
	
	TObjectPtr<USceneComponent> Root;
	UFUNCTION()
	void OnPickUpOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Gameplay")
	void HandlePickUP(ADA_Hero* Hero);
	
	
};
