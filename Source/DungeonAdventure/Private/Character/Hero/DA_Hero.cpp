// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Hero/DA_Hero.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADA_Hero::ADA_Hero()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->SetAbsolute(false, true, false);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = 800.0f;
	
	
	HitComponent = CreateDefaultSubobject<UBoxComponent>("Hit Detection");
	HitComponent->SetupAttachment(GetRootComponent());
	HitComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	
	MoveAxis = FVector2D(0.f, 1.f);
}

void ADA_Hero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADA_Hero::Move);
	
	}
}

void ADA_Hero::Move(const FInputActionValue& InputActionValue)
{
	MoveAxis = InputActionValue.Get<FVector2D>();
	const FVector MoveDirection = FVector(MoveAxis.X, MoveAxis.Y, 0);
	AddMovementInput(MoveDirection, 1);
}
