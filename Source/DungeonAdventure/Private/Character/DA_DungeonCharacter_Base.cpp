// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DA_DungeonCharacter_Base.h"

#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ADA_DungeonCharacter_Base::ADA_DungeonCharacter_Base()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0,1080,0);
	GetSprite()->SetAbsolute(false,true,false);
	bUseControllerRotationYaw = false;
}
