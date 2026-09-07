// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DA_SpawnManager.generated.h"

class ADA_Hero;
class UBoxComponent;
class ADA_PickUp;
class ADA_Enemy_Base;

UCLASS()
class DUNGEONADVENTURE_API ADA_SpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	

	ADA_SpawnManager();

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UBoxComponent> SpawnArea;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float MinSpawnDistance;
	
	UFUNCTION(blueprintCallable)
	virtual void SpawnEnemyInRandomBox(TSubclassOf<ADA_Enemy_Base> ClassToSpawn);
	
	UFUNCTION(blueprintCallable)
	virtual void SpawnEnemy(TSubclassOf<ADA_Enemy_Base> ClassToSpawn,const FTransform& SpawnLocation);
	
	UFUNCTION(blueprintCallable)
	virtual void SpawnPickUP(TSubclassOf<ADA_PickUp> ClassToSpawn,const FVector& SpawnLocation);
	
	
	virtual void BeginPlay() override;
	
	TWeakObjectPtr<ADA_Hero> Hero;
	
};
