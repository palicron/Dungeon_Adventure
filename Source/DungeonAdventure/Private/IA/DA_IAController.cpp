// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/DA_IAController.h"

#include "Character/Enemies/DA_Enemy_Base.h"
#include "Character/Hero/DA_Hero.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ADA_IAController::ADA_IAController()
{
}

void ADA_IAController::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ADA_Hero>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void ADA_IAController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossesPawn = Cast<ADA_Enemy_Base>(InPawn);
	
}

void ADA_IAController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (!Player.IsValid() || !PossesPawn.IsValid())
	{
		return;
	}
	FVector PlayerLocation = Player->GetActorLocation();
	FVector PossesPawnLocation = PossesPawn->GetActorLocation();
	PlayerLocation.Z = 0;
	PossesPawnLocation.Z = 0;
	
	FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(PossesPawnLocation,PlayerLocation);

	PossesPawn->WalkTowards(LookRotation.Vector());
}
