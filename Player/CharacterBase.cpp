// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Components/StaticMeshComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

ACharacterBase::ACharacterBase()
{
	weapon_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	//weapon_mesh->SetupAttachment(GetMesh());
	weapon_mesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weapon_r"));

	shield_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	shield_mesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("shield_l"));

	is_attacking = false;
	combo_counter = 0;

	SetupStimulus();
}

void ACharacterBase::Tick(float DeltaSeconds)
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, FString::Printf(TEXT("is_attacking: %i"), is_attacking));
}

void ACharacterBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterBase::OnPressAttackButton);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ACharacterBase::OnReleaseAttachButton);
}

void ACharacterBase::OnPressAttackButton()
{

	if(!is_attacking && combo_counter == 0)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(sword_attack1);
		combo_counter++;
	}
	else if (is_attacking && combo_counter == 1)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(sword_attack2);
		combo_counter++;
	}
	else if(is_attacking && combo_counter == 2)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(sword_attack3);
		combo_counter = 0;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("is_attacking: %i"), is_attacking));
}

void ACharacterBase::OnReleaseAttachButton()
{
		//is_attacking = false;
}

void ACharacterBase::SetupStimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Component"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}
