// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Hero/DA_Hero.h"

#include "EnhancedInputComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Component/DA_HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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
	
	bIsStunned = false;
	bAttacking = false;
	
	AttackPlayRate = 2.f;
}

void ADA_Hero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADA_Hero::Move);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ADA_Hero::Attack);
	}
}

void ADA_Hero::Move(const FInputActionValue& InputActionValue)
{
	if (!CanTakeAction())
	{
		return;
	}
	MoveAxis = InputActionValue.Get<FVector2D>();
	const FVector MoveDirection = FVector(MoveAxis.X, MoveAxis.Y, 0);
	AddMovementInput(MoveDirection, 1);
}

void ADA_Hero::Attack()
{
	if (!CanTakeAction())
	{
		return;
	}
	
	if (UPaperZDAnimationComponent* AnimComp = GetAnimationComponent())
	{
		if (UPaperZDAnimInstance* PaperZDAnimInst = AnimComp->GetAnimInstance())
		{
			FZDOnAnimationOverrideEndSignature OnAttackCompleteDelegate;
			OnAttackCompleteDelegate.BindWeakLambda(this, [&](bool bComplete)
			{
				bAttacking = false;
			});
			PaperZDAnimInst->PlayAnimationOverride(AttackSequence, "DefaultSlot", AttackPlayRate, 0.f, OnAttackCompleteDelegate);
			
			bAttacking = true;
		}
	}
}


float ADA_Hero::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (!DamageCauser)
	{
		return 0.f;
	}
	
	const bool bIsDead = HealthComponent->TakeIncomingDamage(DamageAmount);
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %hhd"), bIsDead));
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

bool ADA_Hero::CanTakeAction() const
{
	return !bIsStunned && !HealthComponent->IsDead() && !bAttacking ;
}

void ADA_Hero::OnDamageTaken(float DamageTaken)
{
	
	if (!HitSequence)
	{
		return;
	}

	if (UPaperZDAnimationComponent* AnimComp = GetAnimationComponent())
	{
		if (UPaperZDAnimInstance* PaperZDAnimInst = AnimComp->GetAnimInstance())
		{
			FZDOnAnimationOverrideEndSignature OnCompletedDelegate;
			OnCompletedDelegate.BindWeakLambda(this, [&](bool bComplete)
			{
				bIsStunned = false;
				if (HealthComponent->IsDead())
				{
					if (UPaperZDAnimationComponent* AnimComp = GetAnimationComponent())
					{
						if (UPaperZDAnimInstance* PaperZDAnimInst = AnimComp->GetAnimInstance())
						{
							PaperZDAnimInst->JumpToNode("DefeatJump");
						}
					}
					
				}
			});
			PaperZDAnimInst->PlayAnimationOverride(HitSequence, "DefaultSlot", 1, 0.f, OnCompletedDelegate);
			bIsStunned = true;
		}
	}
	
}

void ADA_Hero::CheckDamageHitComponent()
{
	TArray<AActor*> OverlappingActors;
	HitComponent->GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor != this)
		{
			UGameplayStatics::ApplyDamage(OverlappingActor,10.f,GetController(),this, UDamageType::StaticClass());
		}
	}
}
