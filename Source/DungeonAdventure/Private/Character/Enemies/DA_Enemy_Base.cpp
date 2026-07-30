// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemies/DA_Enemy_Base.h"

void ADA_Enemy_Base::WalkTowards(const FVector& Direction)
{
	AddMovementInput(Direction, 1);
}
