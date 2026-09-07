// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/DA_SpawnManager.h"

#include "Character/Enemies/DA_Enemy_Base.h"
#include "Character/Hero/DA_Hero.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PickUp/DA_PickUp.h"

// Sets default values
ADA_SpawnManager::ADA_SpawnManager()
{
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(Root);
	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnArea->SetCollisionResponseToAllChannels(ECR_Ignore);
	MinSpawnDistance = 200.f;
	
}

void ADA_SpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	Hero = Cast<ADA_Hero>(UGameplayStatics::GetPlayerPawn(this, 0));
}


void ADA_SpawnManager::SpawnEnemyInRandomBox(TSubclassOf<ADA_Enemy_Base> ClassToSpawn)
{
	if (!ClassToSpawn || !Hero.IsValid())
	{
		return;
	}
	
	bool bFoundSpawnArea = false;
	FVector RandomLocation;
	while (!bFoundSpawnArea)
	{
		RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->GetBounds().Origin, SpawnArea->GetBounds().BoxExtent);
		RandomLocation.Z = 100;
		
		if (FVector::Dist(Hero->GetActorLocation(), RandomLocation) > MinSpawnDistance)
		{
			bFoundSpawnArea = true;
		}
	}
	

	
	
	FTransform SpawnLocation;
	SpawnLocation.SetLocation(RandomLocation);
	
	SpawnEnemy(ClassToSpawn, SpawnLocation);
}

void ADA_SpawnManager::SpawnEnemy(const TSubclassOf<ADA_Enemy_Base> ClassToSpawn, const FTransform& SpawnLocation)
{
	if (!ClassToSpawn)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	

	
	
	
	GetWorld()->SpawnActor<ADA_Enemy_Base>(ClassToSpawn, SpawnLocation, SpawnParams);
}

void ADA_SpawnManager::SpawnPickUP(TSubclassOf<ADA_PickUp> ClassToSpawn, const FVector& SpawnLocation)
{
	if (!ClassToSpawn)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor<ADA_PickUp>(ClassToSpawn, SpawnLocation,FRotator::ZeroRotator, SpawnParams);
}





